/*
 * Copyright (C) 2005-2017 Centre National d'Etudes Spatiales (CNES)
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

#include "otbWrapperQtWidgetListEditWidget.h"
#include "ui_otbWrapperQtWidgetListEditWidget.h"


/*****************************************************************************/
/* INCLUDE SECTION                                                           */

//
// Qt includes (sorted by alphabetic order)
//// Must be included before system/custom includes.

//
// System includes (sorted by alphabetic order)

//
// ITK includes (sorted by alphabetic order)

//
// OTB includes (sorted by alphabetic order)
#include "otbQtAdapters.h"
#include "otbWrapperQtWidgetListEditItemModel.h"
#include "otbWrapperTypes.h"

namespace otb
{

namespace Wrapper
{

/*
  TRANSLATOR otn::Wrappers

  Necessary for lupdate to be aware of C++ namespaces.

  Context comment for translator.
*/


/*****************************************************************************/
/* CONSTANTS                                                                 */


/*****************************************************************************/
/* STATIC IMPLEMENTATION SECTION                                             */


/*****************************************************************************/
/* CLASS IMPLEMENTATION SECTION                                              */
/*****************************************************************************/
ListEditWidget
::ListEditWidget( QWidget * p, Qt::WindowFlags flags ) :
  QWidget( p, flags ),
  m_UI( new otb::Wrapper::Ui::ListEditWidget() )
{
  m_UI->setupUi( this );

  assert( m_UI->browseButton!=nullptr );

  {
  assert( m_UI->treeView->selectionModel()==nullptr );

  m_UI->treeView->setModel( new ListEditItemModel( m_UI->treeView ) );

  assert( m_UI->treeView->selectionModel()!=nullptr );

  QObject::connect(
    m_UI->treeView->selectionModel(),
    SIGNAL(
      selectionChanged( const QItemSelection & , const QItemSelection & )
    ),
    // to:
    this,
    SLOT(
      onSelectionChanged( const QItemSelection & , const QItemSelection & )
    )
  );
  }
}

/*******************************************************************************/
ListEditWidget
::~ListEditWidget()
{
  delete m_UI;
  m_UI = nullptr;
}

/*****************************************************************************/
void
ListEditWidget
::SetBrowseEnabled( bool enabled )
{
  assert( m_UI!=nullptr );
  assert( m_UI->browseButton );

  m_UI->browseButton->setEnabled( enabled );
}

/*******************************************************************************/
bool
ListEditWidget
::IsBrowseEnabled() const
{
  assert( m_UI!=nullptr );
  assert( m_UI->browseButton );

  return m_UI->browseButton->isEnabled();
}

/*******************************************************************************/
const ListEditItemModel *
ListEditWidget
::GetItemModel() const
{
  return const_cast< ListEditWidget * >( this )->GetItemModel();
}

/*******************************************************************************/
ListEditItemModel *
ListEditWidget
::GetItemModel()
{
  assert(
    m_UI->treeView->model()==
    qobject_cast< ListEditItemModel * >( m_UI->treeView->model() )
    );

  return qobject_cast< ListEditItemModel * >( m_UI->treeView->model() );
}

/*******************************************************************************/
void
ListEditWidget
::Swap( int row1, int row2, SwapSelection s )
{
  assert( GetItemModel()!=nullptr );

  assert( row1>=0 );
  assert( row1<GetItemModel()->rowCount() );

  assert( row2>=0 );
  assert( row2<GetItemModel()->rowCount() );


  ListEditItemModel * itemModel = GetItemModel();

  assert( itemModel!=nullptr );


  itemModel->Swap( row1, row2 );


  {
    int row =
      s==LEFT
      ? row1
      : ( s==RIGHT
	  ? row2
	  : -1 );

    if( row<0 )
      return;

    assert( m_UI!=nullptr );
    assert( m_UI->treeView!=nullptr );
    assert( m_UI->treeView->selectionModel()!=nullptr );

    QItemSelectionModel * ism =  m_UI->treeView->selectionModel();

    assert( ism!=nullptr );

    ism->clear();

    ism->setCurrentIndex(
      itemModel->index( row, ListEditItemModel::COLUMN_NAME ),
      QItemSelectionModel::Clear |
      QItemSelectionModel::Select |
      QItemSelectionModel::Current |
      QItemSelectionModel::Rows
    );
  }
}

/*******************************************************************************/
QString
ListEditWidget
::browseFilename( const QString & filename )
{
  const ListEditItemModel * itemModel = GetItemModel();
  assert( itemModel!=nullptr );

  QString filePath(
    QDir::current().filePath(
      filename
    )
  );

  QString selectedFilter;

  return
    itemModel->IsInput()
    ? GetOpenFileName(
        this,
	tr( "Select input filename..." ),
	filePath,
	itemModel->GetFilter(),
	&selectedFilter
      )
    : GetSaveFileName(
        this,
	tr( "Select output filename..." ),
	filePath,
	itemModel->GetFilter(),
	&selectedFilter
      );
}

/*******************************************************************************/
QString
ListEditWidget
::browseFilename( const QModelIndex & index )
{
  assert( index.isValid() );
  assert( index.row()>=0 );
  assert( index.column()>=0 );

  //
  // Get item-model.
  const ListEditItemModel * itemModel = GetItemModel();
  assert( itemModel!=nullptr );

  //
  // Pick-up filename.
  assert(
    itemModel->data( index, ListEditItemModel::USER_ROLE_DIRECTION ).isValid()
  );

  assert(
    itemModel->data( index, ListEditItemModel::USER_ROLE_DIRECTION )==Role_Input
    ||
    itemModel->data( index, ListEditItemModel::USER_ROLE_DIRECTION )==Role_Output
  );

  return
    browseFilename( itemModel->data( index ).toString() );
}


/*******************************************************************************/
/* SLOTS                                                                       */
/*******************************************************************************/
void
ListEditWidget
::on_addButton_clicked()
{
  // qDebug() << this << "::on_addButton_clicked()";

  ListEditItemModel * itemModel = GetItemModel();
  assert( itemModel!=nullptr );

  //
  // When not browsable
  if( !itemModel->IsBrowsable() )
    {
    itemModel->insertRow( itemModel->rowCount() );

    return;
    }

  //
  // When browsable.
  QString filename( browseFilename() );

  if( filename.isEmpty() )
    return;

  int row = itemModel->rowCount();
  assert( row>=0 );

  if( !itemModel->insertRow( row ) )
    return;

  itemModel->setData(
    itemModel->index( row, ListEditItemModel::COLUMN_NAME ),
    filename
  );
}

/*******************************************************************************/
void
ListEditWidget
::on_removeButton_clicked()
{
  // qDebug() << this << "::on_removeButton_clicked()";

  assert( m_UI->treeView->selectionModel()!=nullptr );


  QModelIndexList indexes(
    m_UI->treeView->selectionModel()->selectedRows()
  );

  if( indexes.empty() )
    return;


  ListEditItemModel * itemModel = GetItemModel();

  assert( itemModel!=nullptr );


  for( const QModelIndex & i : indexes )
    {
    assert( i.isValid() );

    itemModel->removeRow( i.row() );
    }
}

/*******************************************************************************/
void
ListEditWidget
::on_upButton_clicked()
{
  // qDebug() << this << "::on_upButton_clicked()";

  assert( m_UI!=nullptr );
  assert( m_UI->treeView!=nullptr );
  assert( m_UI->treeView->selectionModel()!=nullptr );


  QModelIndexList indexes(
    m_UI->treeView->selectionModel()->selectedRows()
  );

  if( indexes.empty() )
    return;

  assert( indexes.size()==1 );


  const QModelIndex & front = indexes.front();

  if( front.row()<1 )
    return;


  Swap(
    front.row(),
    front.row() - 1,
    RIGHT
  );
}

/*******************************************************************************/
void
ListEditWidget
::on_downButton_clicked()
{
  // qDebug() << this << "::on_downButton_clicked()";

  assert( m_UI!=nullptr );
  assert( m_UI->treeView!=nullptr );
  assert( m_UI->treeView->selectionModel()!=nullptr );


  QModelIndexList indexes(
    m_UI->treeView->selectionModel()->selectedRows()
  );

  if( indexes.empty() )
    return;

  assert( indexes.size()==1 );


  const QModelIndex & front = indexes.front();

  if( front.row() >= GetItemModel()->rowCount() - 1 )
    return;


  Swap(
    front.row(),
    front.row() + 1,
    RIGHT
  );
}

/*******************************************************************************/
void
ListEditWidget
::on_browseButton_clicked()
{
  // qDebug() << this << "::on_browseButton_clicked()";

  assert( m_UI!=nullptr );
  assert( m_UI->treeView!=nullptr );
  assert( m_UI->treeView->selectionModel()!=nullptr );


  //
  // Pick-up first item of selection.
  QModelIndexList indexes(
    m_UI->treeView->selectionModel()->selectedRows()
  );

  if( indexes.isEmpty() )
    return;

  assert( indexes.size()==1 );

  const QModelIndex & front = indexes.front();

  //
  // Get item-model.
  ListEditItemModel * itemModel = GetItemModel();
  assert( itemModel!=nullptr );

  //
  // Pick-up filename.
  QString selectedFilter;

  QString filename( browseFilename( front ) );

  if( filename.isEmpty() )
    return;

  //
  // Foo.
  itemModel->setData( front, filename );
}

/*******************************************************************************/
void
ListEditWidget
::onSelectionChanged( const QItemSelection & /* selected */,
		      const QItemSelection & /* deselected */ )
{
  // qDebug()
  //   << this
  //   << "::onSelectionChanged(" << selected << "," << deselected << ")";
}

} // end namespace 'Wrapper'

} // end namespace 'otb'
