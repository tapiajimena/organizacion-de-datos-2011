TEMPLATE = app
TARGET = QT_Tree
QT += core
HEADERS += Common/Comparable.h \
    Common/DuplicateRecord.h \
    Common/FileManager.h \
    Common/InvalidKeyException.h \
    Common/OverflowdedBucketException.h \
    Common/OversizedInsertionException.h \
    Common/OversizedRecordException.h \
    Common/Record.h \
    Common/Serializable.h \
    src/BPlusTree.h \
    src/BPlusTree_CONST.h \
    src/InternalNode.h \
    src/LeafNode.h \
    src/Node.h \
    src/NodeFactory.h
SOURCES += Common/FileManager.cpp \
    Common/Record.cpp \
    src/BPlusTree.cpp \
    src/InternalNode.cpp \
    src/LeafNode.cpp \
    src/Node.cpp \
    src/NodeFactory.cpp \
    src/Tree.cpp \
    src/tests.cpp
FORMS += 
RESOURCES += 
