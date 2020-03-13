#ifndef FELGOLIVECLIENT_H
#define FELGOLIVECLIENT_H

#include <QObject>
#include <QQmlEngine>
#include <QApplication>
#include <QString>
#include <QPointer>

class VPlayLiveEngine;
class WebReceiver;
class Broadcast;

class FelgoLiveClient : public QObject
{
  Q_OBJECT

  Q_PROPERTY(QString clientName READ clientName WRITE setClientName NOTIFY clientNameChanged)

public:
  explicit FelgoLiveClient(QQmlEngine *engine, QObject *parent = 0);
  void setWelcomeQmlFile(const QString &file);

  QString clientName();
  void setClientName(const QString &clientName);

signals:
  void webReceiverConnectionRefused(const QString &reason);
  void webReceiverConnected();
  void receivedMatchId(const QString &matchId);
  void pendingProject(const QString &projectName, const QString& projectMainFile);
  void clientNameChanged(const QString &clientName);

public slots:
  void loadProject(const QString& projectName, const QString& projectMainFile);
  void clearProjects();
  void clearProject(const QString& projectName);
  void connectAsLocalDesktopClient(const QUrl &serverUrl);
  void connectToLocalServer(const QUrl &serverUrl, const QString &userId, const QString &deviceId);
  void connectToWebServer(const QString &userId, const QString &deviceId);

private slots:
  void connectWebReceiver(const QUrl &serverUrl, const QString &userId, const QString &deviceId, bool local);
  void disconnectWebReceiver();
  void onProjectChanged(const QString& projectName, const QString& projectMainFile);
  void shakeDetected();
  void onDocumentUpdated(const QString &document, const QString &content);
  void prepareLoadingDocument();
  void modifyLoadedDocument();

private:
  void disableDisplaySleep();
  void addShakeDetection();
  void setQmlEngine(QQmlEngine *engine);

private:
  QString m_welcomeQmlFile;
  QPointer<QQmlEngine> m_engine;
  QPointer<VPlayLiveEngine> m_liveEngine;
  QPointer<WebReceiver> m_webReceiver;
  QPointer<Broadcast> m_broadcast;

  QString m_udid;
  QString m_appIdentifier;
  QString m_clientName;
};

#endif // FELGOLIVECLIENT_H
