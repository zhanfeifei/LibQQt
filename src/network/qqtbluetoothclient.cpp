﻿#include "qqtbluetoothclient.h"
#include <qqtcore.h>

QQtBluetoothClient::QQtBluetoothClient ( QBluetoothServiceInfo::Protocol socketType, QObject* parent ) :
    QBluetoothSocket ( socketType, parent )
{
    initSocket();
}

QQtBluetoothClient::QQtBluetoothClient ( QObject* parent ) : QBluetoothSocket ( parent )
{
    initSocket();
}

void QQtBluetoothClient::initSocket()
{
    connect ( this, SIGNAL ( stateChanged ( QBluetoothSocket::SocketState ) ),
              this, SLOT ( socketStateChanged ( QBluetoothSocket::SocketState ) ) );
    // connected
    connect ( this, SIGNAL ( connected() ),
              this, SLOT ( socketConnected() ) );
    // disconnected
    connect ( this, SIGNAL ( disconnected() ),
              this, SLOT ( socketDisconnect() ) );
    // error
    connect ( this, SIGNAL ( error ( QBluetoothSocket::SocketError ) ),
              this, SLOT ( socketErrorOccured ( QBluetoothSocket::SocketError ) ) );

    connect ( this, SIGNAL ( readyRead() ),
              this, SLOT ( readyReadData() ) );

    connect ( this, SIGNAL ( bytesWritten ( qint64 ) ),
              this, SLOT ( updateProgress ( qint64 ) ) );

    connect ( this, SIGNAL ( bytesWritten ( qint64 ) ),
              this, SIGNAL ( signalUpdateProgress ( qint64 ) ) );

    m_PORT = 0;
    m_protocol = nullptr;
}

void QQtBluetoothClient::installProtocol ( QQtProtocol* stack )
{
    if ( m_protocol )
        return;

    connect ( stack, SIGNAL ( write ( const QByteArray& ) ),
              this, SLOT ( slotWriteData ( const QByteArray& ) ) );
    stack->attach();
    m_protocol = stack;
}

void QQtBluetoothClient::uninstallProtocol ( QQtProtocol* stack )
{
    Q_UNUSED ( stack )

    if ( !m_protocol )
        return;

    disconnect ( m_protocol, SIGNAL ( write ( const QByteArray& ) ),
                 this, SLOT ( slotWriteData ( const QByteArray& ) ) );
    m_protocol->detach();
    m_protocol = NULL;
}

QQtProtocol* QQtBluetoothClient::installedProtocol()
{
    return m_protocol;
}

void QQtBluetoothClient::sendConnectMessage()
{
    pline() << isOpen() << state();

    if ( !isOpen() )
    {
        connectToSingelHost();
        return;
    }

    if ( state() == ServiceLookupState ||
         state() == ConnectingState )
    {
        emit signalConnecting();
        return;
    }

    if ( state() == ConnectedState )
        emit signalConnectSucc();

    return;
}


int QQtBluetoothClient::sendDisConnectFromHost()
{
    pline() << isOpen() << state();

    if ( isOpen() )
    {
#if defined(__WIN32__) || defined (__WIN64__)
        ;
#else
        shutdown ( this->socketDescriptor(), SHUT_RDWR );
#endif
        disconnectFromService();
        close();
        emit signalDisConnectSucc();
    }

    return true;
}

/**
 * @brief QQtBluetoothClient::socketStateChanged
 * @param eSocketState
 * 状态函数
 */
void QQtBluetoothClient::socketStateChanged ( QBluetoothSocket::SocketState eSocketState )
{
    pline() << eSocketState;

    switch ( eSocketState )
    {
        case ServiceLookupState:
        case ConnectingState:
            break;

        case ConnectedState:
            break;

        case ClosingState:
            break;

        case UnconnectedState:
            break;

        default:
            break;
    }
}

/**
 * @brief QQtBluetoothClient::socketErrorOccured
 * @param e
 * 状态函数
 */
void QQtBluetoothClient::socketErrorOccured ( QBluetoothSocket::SocketError e )
{
    /*
     * 在错误状态下重新连接其他热点，直到确定连接类型，写入配置文件
     */
    pline() << e << errorString();

    switch ( e )
    {
        case HostNotFoundError:
        default:
            emit signalConnectFail();
            break;
    }
}

/**
 * @brief QQtBluetoothClient::socketConnected
 * 功能接口
 */
void QQtBluetoothClient::socketConnected()
{
    pline() << peerName() << peerAddress().toString() << peerPort();
    /*
     * 这个步骤，socket重建，资源重新开始
     */
    emit signalConnectSucc();
}

/**
 * @brief QQtBluetoothClient::socketDisconnect
 * 功能接口
 */
void QQtBluetoothClient::socketDisconnect()
{
    pline();
}

void QQtBluetoothClient::updateProgress ( qint64 bytes )
{
    Q_UNUSED ( bytes )
    //pline() << bytes;
}

void QQtBluetoothClient::connectToSingelHost()
{
    if ( !m_uuid.isNull() )
    {
        connectToService ( m_serverIP, m_uuid );
        pline() << peerName() << m_uuid;
    }
    else if ( m_serviceInfo.isValid() )
    {
        connectToService ( m_serviceInfo );
        pline() << m_serviceInfo;
    }
    else if ( m_PORT != 0 )
    {
        connectToService ( m_serverIP, m_PORT );
        pline() << peerName() << m_PORT;
    }
}



void QQtBluetoothClient::readyReadData()
{
    QByteArray bytes;
    bytes = readAll();
    translator ( bytes );
}

void QQtBluetoothClient::slotWriteData ( const QByteArray& bytes )
{
    write ( bytes );
}

void QQtBluetoothClient::translator ( const QByteArray& bytes )
{
    // queued conn and queued package;
    // direct conn and direct package;
    /**
     * 这个地方的实现，还是有一些复杂，
     * 但是只有流式传输才需要，
     * 而且，每种通讯接口的流式传输都是一样的，
     * 过去，写在protocol里是为了增添传输工具客户端类型方便
     * 现在，这块比较稳定，所以挪动回来。
     *
     * 只能安装一个协议。
     * 如果安装多个，这个地方的static，需要给协议们分配独立的buffer。
     * 一个客户端，和服务器通信，一条流，可以由多个协议进行解析吗？
     */
    static QByteArray sqbaBlockOnNet;
    sqbaBlockOnNet += bytes;
    //qint64 aaa = bytesAvailable();
    //pline() << aaa;

    do
    {
        quint16 nBlockLen = m_protocol->splitter ( sqbaBlockOnNet );

        pmeta ( this ) << sqbaBlockOnNet.size() << "..." << nBlockLen;

        if ( sqbaBlockOnNet.length() < nBlockLen || nBlockLen < m_protocol->minlength() )
        {
            /*
             * 收到数据不足或者解析包长小于最小包长
             */
            return;
        }
        else if ( nBlockLen > m_protocol->maxlength() )
        {
            /*
             * 数据包长超过了最大长度
             */
            sqbaBlockOnNet.clear();
            pmeta ( this ) << "forbidden package" << sqbaBlockOnNet.length() << nBlockLen;
            return;
        }
        else if ( sqbaBlockOnNet.length() > nBlockLen )
        {
            /*
             * 粘包
             * 还没有处理完毕，数据已经接收到，异步信号处理出现这种异常
             * 疑问:如果异步调用这个函数绘出现什么问题？正常情况，同步获取数据，异步处理；检测异步获取并且处理会有什么状况
             */
            pmeta ( this ) << "stick package" << sqbaBlockOnNet.length() << nBlockLen;
            QByteArray netData;
            netData.resize ( nBlockLen );
            sqbaBlockOnNet >> netData;
            m_protocol->dispatcher ( netData );
            continue;
        }

        /*
         * 正常分发
         */
        m_protocol->dispatcher ( sqbaBlockOnNet );
        break;
    } while ( 1 );

    sqbaBlockOnNet.clear();
}
