#include "configuration.h"

#include <fstream>

namespace tomato {

const char CONFIGURATION_PATH[] = "etc/tomato.conf";

extern Configuration g_configuration = Configuration();

extern const QString Configuration::NO_USING_TAG = QString("空");// = QString::Null;

QColor no_tag_color(Qt::black);

std::wistream& operator>>(std::wistream& in,
    ConfigurationData& configuration_data) {
  in.imbue(std::locale("zh_CN.UTF-8"));
  in >> configuration_data.tag;
  in.imbue(std::locale("C"));
  in >> configuration_data.red >> configuration_data.green >> configuration_data.yellow;
  return in;
}

std::wostream& operator<<(std::wostream& out,
    const ConfigurationData& configuration_data ) {
  out.imbue(std::locale("zh_CN.UTF-8"));
  out << configuration_data.tag;
  out.imbue(std::locale("C"));
  out << L" " << configuration_data.red << L" " << configuration_data.green
      << L" " << configuration_data.yellow << std::endl;
  return out;
}


QConfigurationData::QConfigurationData(const ConfigurationData& configuration_data) {
  tag = QString::fromStdWString(configuration_data.tag);
  color = QColor(configuration_data.red, configuration_data.green,
                 configuration_data.yellow);
}


Configuration::Configuration() {
 // file_ = new QFile(path);
  configuration_data_.clear();
  Load();
}

Configuration::~Configuration() {
  configuration_data_.clear();
}

void Configuration::Load() {
  std::wifstream win;
  win.open(CONFIGURATION_PATH, std::ios::in);
  ConfigurationData tmp;
  while (win >> tmp) {
    configuration_data_.push_back(QConfigurationData(tmp));
  }
  win.close();
}

void Configuration::Save() {
  std::wofstream wout;
  wout.open(CONFIGURATION_PATH, std::ios::out);
  for (std::vector<QConfigurationData>::iterator i = configuration_data_.begin();
      i != configuration_data_.end(); ++i) {
    wout << QConfigurationData::ToConfigurationData(*i) << std::endl;
  }
  wout.close();
}

std::vector<QConfigurationData>::const_iterator Configuration::
    BeginForConfigurationData() {
  return configuration_data_.begin();
}

std::vector<QConfigurationData>::const_iterator Configuration::
    EndForConfigurationData() {
  return configuration_data_.end();
}

QColor Configuration::GetColor(QString tag) {
  for (std::vector<QConfigurationData>::iterator i = configuration_data_.begin();
       i != configuration_data_.end(); ++i) {
    if (i->tag == tag) {
      return i->color;
    }
  }
  return no_tag_color;
}

}

