#pragma once
#include "connections-tree/operations.h"
#include "connections-tree/items/treeitem.h"

class ItemOperationsMock : public ConnectionsTree::Operations {

public:
    ItemOperationsMock(bool positive_mode=true):
        m_positive_mode(positive_mode) {}

    DatabaseList databases;
    virtual void getDatabases(std::function<void(DatabaseList)> callback) {
        if (m_positive_mode)
            callback(databases);
        else
            throw ConnectionsTree::Operations::Exception("fake error");
    }

    RawKeysList keys;
    virtual void getDatabaseKeys(uint, std::function<void(const RawKeysList&)> callback) {
        if (m_positive_mode)
            callback(keys);
        else
            throw ConnectionsTree::Operations::Exception("fake error");
    }

    virtual QSharedPointer<Console::Operations> getConsoleOperations()
    {
        return QSharedPointer<Console::Operations>();
    }

    QString namespaceSeparator = ":";
    QString getNamespaceSeparator() { return namespaceSeparator; }

    void disconnect() {}

    virtual void openKeyTab(ConnectionsTree::KeyItem&, bool) override {}
    virtual void openConsoleTab() override {}
    void openNewKeyDialog(int, QString = QString()) override {}

protected:
    bool m_positive_mode;
};

class DummyParentView : public ConnectionsTree::TreeItem::ParentView {

public:
    QWidget* getParentWidget() override
    {
        return nullptr;
    }
};
