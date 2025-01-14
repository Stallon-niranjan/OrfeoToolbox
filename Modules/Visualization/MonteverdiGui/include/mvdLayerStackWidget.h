/*
 * Copyright (C) 2005-2022 Centre National d'Etudes Spatiales (CNES)
 *
 * This file is part of Orfeo Toolbox
 *
 *     https://www.orfeo-toolbox.org/
 *
 * Licensed under the Apache License, Version 2.0 (the "License");
 * you may not use this file except in compliance with the License.
 * You may obtain a copy of the License at
 *
 *     http://www.apache.org/licenses/LICENSE-2.0
 *
 * Unless required by applicable law or agreed to in writing, software
 * distributed under the License is distributed on an "AS IS" BASIS,
 * WITHOUT WARRANTIES OR CONDITIONS OF ANY KIND, either express or implied.
 * See the License for the specific language governing permissions and
 * limitations under the License.
 */

#ifndef mvdLayerStackWidget_h
#define mvdLayerStackWidget_h

//
// Configuration include.
//// Included at first position before any other ones.
#include "ConfigureMonteverdi.h"


/*****************************************************************************/
/* INCLUDE SECTION                                                           */

//
// Qt includes (sorted by alphabetic order)
//// Must be included before system/custom includes.
#include <QtWidgets>

//
// System includes (sorted by alphabetic order)

//
// ITK includes (sorted by alphabetic order)

//
// OTB includes (sorted by alphabetic order)
#include "OTBMonteverdiGUIExport.h"
//
// Monteverdi includes (sorted by alphabetic order)


/*****************************************************************************/
/* PRE-DECLARATION SECTION                                                   */

//
// External classes pre-declaration.
namespace
{
}

namespace mvd
{
class AbstractLayerModel;
class LayerStackItemModel;

//
// Internal classes pre-declaration.
namespace Ui
{
class LayerStackWidget;
};


/*****************************************************************************/
/* CLASS DEFINITION SECTION                                                  */

/**
 * \class LayerStackWidget
 *
 * \ingroup OTBMonteverdiGUI
 *
 * \brief Widget template skeleton to copy-paste when adding a new
 * widget class.
 */
class OTBMonteverdiGUI_EXPORT LayerStackWidget : public QWidget
{

  /*-[ QOBJECT SECTION ]-----------------------------------------------------*/

  Q_OBJECT;

  /*-[ PUBLIC SECTION ]------------------------------------------------------*/

  //
  // Public methods.
public:
  /** \brief Constructor. */
  LayerStackWidget(QWidget* p = NULL, Qt::WindowFlags flags = 0);

  /** \brief Destructor. */
  ~LayerStackWidget() override;

  /**
   */
  const LayerStackItemModel* GetItemModel() const;

  /**
   */
  LayerStackItemModel* GetItemModel();

  /**
   */
  void SetCurrent(int);

  /**
   */
  void SetApplyEnabled(bool);

  /**
   */
  void SetDeleteEnabled(bool);

  /**
   */
  void SetMoveEnabled(bool);

  /**
   */
  void SetProjectionEnabled(bool);

  /**
   */
  void SetReloadEnabled(bool);

  void SetResetEffectsEnabled(bool);

  /**
   */
  void InstallEventFilter(QObject* filter);

  //
  // QObject overloads.
  //

  /**
   * \see http://qt-project.org/doc/qt-4.8/qobject.html#eventFilter
   */
  bool eventFilter(QObject* watched, QEvent* event) override;

  /*-[ PUBLIC SLOTS SECTION ]------------------------------------------------*/

  //
  // Public SLOTS.
public Q_SLOTS:

  /*-[ SIGNALS SECTION ]-----------------------------------------------------*/

  //
  // Signals.
Q_SIGNALS:
  /**
  */
  // bugFix for layer deletion
  void LayerDeletingWidget(unsigned int index);
  /**
   */
  void CurrentChanged(int);
  /**
   */
  void SelectionChanged(int);
  /**
   */
  void TopButtonClicked();
  /**
   */
  void BottomButtonClicked();
  /**
   */
  void UpButtonClicked();
  /**
   */
  void DownButtonClicked();
  /**
   */
  void DeleteLayerRequested();
  /**
   */
  void DeleteAllLayersRequested();
  /**
   */
  void RotateLayersRequested(int);
  /**
   */
  void ProjectionButtonClicked();
  /**
   */
  void ApplyButtonClicked();
  /**
   */
  void ResetEffectsButtonClicked();
  /**
   */
  void CopyLayerRequested(const AbstractLayerModel*);

  /*-[ PROTECTED SECTION ]---------------------------------------------------*/

  //
  // Protected methods.
protected:
  /*-[ PRIVATE SECTION ]-----------------------------------------------------*/

  //
  // Protected attributes.
protected:
  /**
   * \see http://qt-project.org/doc/qt-4.8/qabstractitemview.html#dropEvent
   */
  // virtual void dopEvent( QDropEvent * event );

  //
  // Private methods.
private:
  //
  // Private attributes.
private:
  /**
   * \brief uic generated.
   */
  Ui::LayerStackWidget* m_UI;

  /*-[ PRIVATE SLOTS SECTION ]-----------------------------------------------*/

  //
  // Slots.
private Q_SLOTS:
  /**
   * \see http://qt-project.org/doc/qt-4.8/qitemselectionmodel.html#currentRowChanged
   */
  void OnCurrentRowChanged(const QModelIndex&, const QModelIndex&);

  /**
   * \see http://qt-project.org/doc/qt-4.8/qitemselectionmodel.html#selectionChanged
   */
  void OnSelectionChanged(const QItemSelection& selected, const QItemSelection& deselected);
};

} // end namespace 'mvd'

/*****************************************************************************/
/* INLINE SECTION                                                            */

namespace mvd
{
} // end namespace 'mvd'

#endif // mvdLayerStackWidget_h
