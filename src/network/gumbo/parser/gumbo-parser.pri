######################################################################
# Automatically generated by qmake (3.1) Mon Nov 20 12:50:02 2017
######################################################################

INCLUDEPATH += .

# The following define makes your compiler warn you if you use any
# feature of Qt which has been marked as deprecated (the exact warnings
# depend on your compiler). Please consult the documentation of the
# deprecated API in order to know how to port your code away from it.
DEFINES += QT_DEPRECATED_WARNINGS

# You can also make your code fail to compile if you use deprecated APIs.
# In order to do so, uncomment the following line.
# You can also select to disable deprecated APIs only up to a certain version of Qt.
#DEFINES += QT_DISABLE_DEPRECATED_BEFORE=0x060000    # disables all the APIs deprecated before Qt 6.0.0

# Input
HEADERS += $$PWD/src/attribute.h \
           $$PWD/src/char_ref.h \
           $$PWD/src/error.h \
           $$PWD/src/gumbo.h \
           $$PWD/src/insertion_mode.h \
           $$PWD/src/parser.h \
           $$PWD/src/string_buffer.h \
           $$PWD/src/string_piece.h \
           $$PWD/src/tag_enum.h \
           $$PWD/src/tag_gperf.h \
           $$PWD/src/tag_sizes.h \
           $$PWD/src/tag_strings.h \
           $$PWD/src/token_type.h \
           $$PWD/src/tokenizer.h \
           $$PWD/src/tokenizer_states.h \
           $$PWD/src/utf8.h \
           $$PWD/src/util.h \
           $$PWD/src/vector.h

SOURCES += $$PWD/src/attribute.c \
           $$PWD/src/char_ref.c \
           $$PWD/src/error.c \
           $$PWD/src/parser.c \
           $$PWD/src/string_buffer.c \
           $$PWD/src/string_piece.c \
           $$PWD/src/tag.c \
           $$PWD/src/tokenizer.c \
           $$PWD/src/utf8.c \
           $$PWD/src/util.c \
           $$PWD/src/vector.c

win32 {
    HEADERS += $$PWD/visualc/include/strings.h
}
