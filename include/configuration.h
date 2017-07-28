#ifndef TOMATO_CONFIGURATION_H
#define TOMATO_CONFIGURATION_H

#include <vector>
#include <string>

#include <QString>
#include <QColor>

namespace tomato {

struct ConfigurationData {
  friend std::wostream& operator<<(std::wostream& out,
      const ConfigurationData& configuration_data );
  friend std::wistream& operator>>(std::wistream& in,
    ConfigurationData& configuration_data);

  std::wstring tag;
  int red;
  int green;
  int yellow;
};

struct QConfigurationData {
  QConfigurationData(const ConfigurationData& configuration_data);
  static ConfigurationData ToConfigurationData(
      const QConfigurationData& qconfiguration_data) {
    ConfigurationData tmp;
    tmp.tag = (qconfiguration_data.tag).toStdWString();
    tmp.red = qconfiguration_data.color.red();
    tmp.green = qconfiguration_data.color.green();
    tmp.yellow = qconfiguration_data.color.yellow();
    return tmp;
  }

  QString tag;
  QColor color;
};

class Configuration {
public:
  //Configuration(std::string path);
  Configuration();
  ~Configuration();
  static const QString NO_USING_TAG;
  void Save();
  void Load();
  std::vector<QConfigurationData>::const_iterator BeginForConfigurationData();
  std::vector<QConfigurationData>::const_iterator EndForConfigurationData();
  QColor GetColor(QString tag);

private:
  std::vector<QConfigurationData> configuration_data_;
};

extern Configuration g_configuration;

}

#endif
