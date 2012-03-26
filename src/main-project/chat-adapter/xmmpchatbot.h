
#ifndef LVK_CA_XMPPCHATBOT_H
#define LVK_CA_XMPPCHATBOT_H

#include <QObject>
#include <QHash>

#include "QXmppClient.h"
#include "QXmppMessage.h"
#include "chatbot.h"

class QXmppVCardIq;
class QMutex;
class QWaitCondition;

namespace Lvk
{

namespace CA
{

class ContactInfo;

/**
 * \brief Chatbot for XMPP chat servers
 */

class XmppChatbot : public Chatbot
{
    Q_OBJECT

public:
    XmppChatbot(QObject *parent = 0);

    ~XmppChatbot();

    /**
     * \brief An enumeration for type of error.
     */
    enum Error {
        SocketError,        ///< Error due to TCP socket
        KeepAliveError,     ///< Error due to no response to a keep alive
        XmppStreamError,    ///< Error due to XML stream
        InternalError       ///< Internal error
    };

    // Lvk::CA::ChatClient interface

    virtual void connectToServer(const QString &user, const QString &passwd, const QString &host);

    virtual void disconnectFromServer();

    virtual void setVirtualUser(VirtualUser *virtualUser);

    virtual VirtualUser *virtualUser();

public slots:
    void messageReceived(const QXmppMessage&);

    void vCardReceived(const QXmppVCardIq&);

signals:
    void connected();

    void disconnected();

    void error(int err);

private slots:
    void emitLocalError(QXmppClient::Error);

private:
    XmppChatbot(XmppChatbot&);
    XmppChatbot& operator=(XmppChatbot&);

    QXmppClient *m_xmppClient;
    VirtualUser *m_virtualUser;
    QHash<QString, ContactInfo> m_contactInfo;

    QMutex *m_contactInfoMutex;
    QWaitCondition *m_waitVCard;

    ContactInfo getContactInfo(const QString &bareJid);
    Error convertToLocalError(QXmppClient::Error err);
};

} //namespace CA

} //namespace Lvk

#endif // LVK_CA_XMPPCHATBOT_H