
//
// This source file is part of appleseed.
// Visit http://appleseedhq.net/ for additional information and resources.
//
// This software is released under the MIT license.
//
// Copyright (c) 2010-2013 Francois Beaune, Jupiter Jazz Limited
// Copyright (c) 2014-2015 Francois Beaune, The appleseedhq Organization
//
// Permission is hereby granted, free of charge, to any person obtaining a copy
// of this software and associated documentation files (the "Software"), to deal
// in the Software without restriction, including without limitation the rights
// to use, copy, modify, merge, publish, distribute, sublicense, and/or sell
// copies of the Software, and to permit persons to whom the Software is
// furnished to do so, subject to the following conditions:
//
// The above copyright notice and this permission notice shall be included in
// all copies or substantial portions of the Software.
//
// THE SOFTWARE IS PROVIDED "AS IS", WITHOUT WARRANTY OF ANY KIND, EXPRESS OR
// IMPLIED, INCLUDING BUT NOT LIMITED TO THE WARRANTIES OF MERCHANTABILITY,
// FITNESS FOR A PARTICULAR PURPOSE AND NONINFRINGEMENT. IN NO EVENT SHALL THE
// AUTHORS OR COPYRIGHT HOLDERS BE LIABLE FOR ANY CLAIM, DAMAGES OR OTHER
// LIABILITY, WHETHER IN AN ACTION OF CONTRACT, TORT OR OTHERWISE, ARISING FROM,
// OUT OF OR IN CONNECTION WITH THE SOFTWARE OR THE USE OR OTHER DEALINGS IN
// THE SOFTWARE.
//

#ifndef APPLESEED_STUDIO_MAINWINDOW_RENDERSETTINGSWINDOW_H
#define APPLESEED_STUDIO_MAINWINDOW_RENDERSETTINGSWINDOW_H

// Qt headers.
#include <QObject>
#include <QString>
#include <QWidget>

// Standard headers.
#include <map>
#include <string>
#include <vector>

// Forward declarations.
namespace appleseed { namespace studio { class ProjectManager; } }
namespace appleseed { namespace studio { class RenderSettingsPanel; } }
namespace renderer  { class Configuration; }
namespace Ui        { class RenderSettingsWindow; }

namespace appleseed {
namespace studio {

//
// Render settings window.
//

class RenderSettingsWindow
  : public QWidget
{
    Q_OBJECT

  public:
    // Constructor.
    RenderSettingsWindow(
        ProjectManager&                 project_manager,
        QWidget*                        parent = 0);

    // Destructor.
    ~RenderSettingsWindow();

    // Load the configurations of the currently open project.
    void reload();

  signals:
    void signal_settings_modified() const;

  private:
    typedef std::vector<RenderSettingsPanel*> PanelCollection;

    // Not wrapped in std::auto_ptr<> to avoid pulling in the UI definition code.
    Ui::RenderSettingsWindow*           m_ui;

    ProjectManager&                     m_project_manager;
    PanelCollection                     m_panels;
    QString                             m_current_configuration_name;
    std::map<std::string, std::string>  m_initial_values;

    void create_connections();

    void create_panels(const renderer::Configuration& config);
    void create_layout();
    void set_panels_enabled(const bool enabled);

    void load_configuration(const QString& name);
    void save_current_configuration();
    renderer::Configuration& get_configuration(const QString& name) const;

    std::map<std::string, std::string> get_widget_values() const;

  private slots:
    void slot_open_configuration_manager_window();
    void slot_change_active_configuration(const QString& configuration_name);
    void slot_save_configuration_and_close();
    void slot_restore_configuration_and_close();
};

}       // namespace studio
}       // namespace appleseed

#endif  // !APPLESEED_STUDIO_MAINWINDOW_RENDERSETTINGSWINDOW_H
