#ifndef FELGOAPPLICATION_H
#define FELGOAPPLICATION_H

#ifndef PRODUCT_LICENSE_KEY
#define PRODUCT_LICENSE_KEY ""
#endif

#include <QObject>
#include <QAbstractAnimation>
#include <QStringList>
#include <QVariantMap>

class VPlayScheduler;
class QQmlEngine;
class System;
class GlobalKeyForwarder;
class VPlayFileUtils;
class VPlayUrlInterceptor;
class QFileSelector;
class VPlayTranslation;

/**
 * Small utility class to synchronize the stepping with the framerate.
 */

//class QTimer;
//class VPStepDriver : public QObject
//{
//  Q_OBJECT

//public:
//  explicit VPStepDriver(VPlayScheduler *scheduler);

//  void start();

//public slots:
//  void tick();

//private:
//  VPlayScheduler *m_vplayScheduler;
//  QTimer *m_timer;
//};


class VPStepDriver : public QAbstractAnimation
{
  Q_OBJECT

public:
  explicit VPStepDriver(VPlayScheduler *scheduler);

  int duration() const;

protected:
  void updateCurrentTime(int currentTime);

private:
  VPlayScheduler *m_vplayScheduler;
};

class /* Q_CORE_EXPORT */ FelgoApplication : public QObject
{
  Q_OBJECT
public:
  explicit FelgoApplication(QObject *parent = 0);

  ~FelgoApplication();

  /*!
   * Makes Felgo available as "import Felgo 3.0".
   * Calls initializeEngine() and registerTypes() internally.
   */
  void initialize(QQmlEngine *engine);
  /*
    This may be called in future by a dynamic QQmlExtensionPlugin
   */
  void initializeEngine(QQmlEngine *engine, const char *uri);
  void registerTypes(const char *uri);


  /*!
   * Call to set a custom contentScale for testing different resources at startup.
   *
   * The fileSelectors are set based on this scale and the config.json information.
   * \param contentScale
   */
  void setContentScaleAndFileSelectors(qreal contentScale);

  /*!
   * Returns the contentScale that got calculated based on the screen size.
   * Useful for custom defining fileSelectors based on this contentScale.
   * For example if the max screen size is 960px, at a given scene width of 480 the contentScale is 2.
   */
  qreal contentScale() const;

  /*!
   * Returns the used scaleFactor for MultiResolutionImage components.
   * It gets calculated in setContentScaleAndFileSelectors().
   * For example if the max screen size is 2000px, at a given scene width of 480 the scaleFactorForImages is 4, because that was set as "internalContentScaleFactor" in contentScaleThresholds().
   */
  qreal scaleFactorForImages() const;

  /*!
   * Set a custom contentScaleThreshold map.
   * After setting a custom contentScaleThresholds map, you probably want to call \c setContentScaleAndFileSelectors(contentScale()); so the fileSelectors are updated.
   *
   * Example:
     \code

      QVariantMap customThresholds;
      QVariantMap sdMap;
      sdMap["scaleThreshold"] = 1;
      sdMap["internalContentScaleFactor"] = 1;
      customThresholds["sd"] = sdMap;
      QVariantMap hdMap;
      hdMap["scaleThreshold"] = 2;
      hdMap["internalContentScaleFactor"] = 2;
      customThresholds["hd"] = hdMap;
      QVariantMap hd2Map;
      hd2Map["scaleThreshold"] = 2.8;
      hd2Map["internalContentScaleFactor"] = 4;
      customThresholds["hd2"] = hd2Map;

      felgo.setContentScaleThresholds(customThresholds);
      felgo.setContentScaleAndFileSelectors(felgo.contentScale());

     \endcode
   */
  void setContentScaleThresholds(QVariantMap contentScaleThresholds);

  /*!
   * Returns the contentScaleThresholds. By default, it is set to
   *
    \code
     {
       "sd": { "scaleThreshold": 1, "internalContentScaleFactor": 1 },
       "hd": { "scaleThreshold": 2, "internalContentScaleFactor": 2 },
       "hd2": { "scaleThreshold": 2.8, "internalContentScaleFactor": 4}
     }
    \endcode
   *
   */
  const QVariantMap &contentScaleThresholds() const;

  /*!
   * Returns the current fileSelectorList. Useful for adding new fileSelectors to the existing ones.
   */
  const QStringList &fileSelectorList() const;
  /*!
   * Use this function to manually set a fileSelectorList.
   * \param selectorList
   */
  void setFileSelectorList(const QStringList &fileSelectorList);

  /*!
    Returns the QFileSelector applied in Felgo apps.
    This includes the +hd2 / +hd fileSelectors, that get applied based on the current contentScale. You can use this function to manually apply QFileSelector::select() for files used outside the QML scope, but e.g. in QGuiApplication based apps.
    To just add custom fileSelectors to the list, use fileSelectorList() and setFileSelectorList() instead.
   */
  QFileSelector &vplayFileSelector() const;


  /*!
      This is only useful for running application with multiple GameWindow instances in it.
      It avoids creating a new window for each of the loaded GameWindow instance. This is especially important on Android, where only a single Window is allowed.
      This function is also useful, if you want to avoid on Desktop to create a new Window for each GameWindow instance in a multi-GameWindow launcher (like Box2dMultiExamplesLoader.qml).

      The reason for GameWindow instances being tricky are the different possibility to load the main qml file:
      \list
      \li QQmlApplicationEngine requires a QQuickWindow as root element with visible set to true to show something.
      \li QQuickWindow (such as in QtQuick2ControlsApplicationViewer.pri) also requires a Window or ApplicationWindow as root element (and sets visible to true by default).
      \li QQuickView (such as in QtQuick2ApplicationViewer.pri) does not allow a Window element as root element - in such cases you could also call this function.
      \endlist

   */
  void setGameWindowIsItem();

  const QString &mainQmlFileName() const;
  /*!
    Adds the \c assets:/ prefix to the filename on Android, if it is not started from resources.
    The suggested way to load a qml file is from resources, because on Android the file selectors with assets dir do not work!
   */
  void setMainQmlFileName(const QString &qmlFileName);

  /*!
   * Set to true to preserve platform-specific default fonts. This is useful when developing cross-platform apps.
   * \param preserve
   */
  void setPreservePlatformFonts(bool preserve);

  /*!
   * Set a Felgo license key from your main.cpp file. Setting the license key here overrides the license key supplied
   * in your Main.qml (App or GameWindow) file.
   */
  void setLicenseKey(const QString &licenseKey);

  QQmlEngine *qmlEngine();

signals:

public slots:
  void objectCreatedHandler(QObject *object, const QUrl &url);

private:
  QQmlEngine *m_engine;
  VPlayScheduler *m_vplayScheduler;
  VPStepDriver *m_stepDriver;
  System *m_system;
  QStringList m_fileSelectorList;
  QString m_mainQmlFileName;
  GlobalKeyForwarder *m_globalKeyForwarder;
  VPlayFileUtils *m_fileUtils;
  VPlayTranslation *m_vplayTranslation;

  VPlayUrlInterceptor *m_vplayUrlInterceptor;
  QFileSelector *m_vplayFileSelector;
  qreal m_contentScale;
  qreal m_scaleFactorForImages;
  QVariantMap m_contentScaleThresholds;

  bool m_preservePlatformFonts;

  /*!
   * Is called from initializeEngine() and sets the default contentScale and fileSelectors based on the screen size.
   */
  void setDefaultContentScalingAndFileSelectors();

  void addCustomImportPaths();
  QString adjustImportPathToCanonical(const QString &path);
  void addImportPath(const QString &path);
};

#endif // FELGOAPPLICATION_H
