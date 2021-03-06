/*
 * File:   MappingToolWindow.h
 * Author: void
 *
 * Created on September 24, 2012, 12:09 AM
 */

#ifndef _MAPPINGTOOLWINDOW_H
#    define	_MAPPINGTOOLWINDOW_H

#    include "ui_MappingToolWindow.hpp"
#    include "IMappingToolWindow.h"
#    include <QtGui/QMenuBar>
#	 include <QtGui/QStandardItem>

SHARED_PTR_FORWARD(QIrrControl);

class MappingToolWindow :
        public QDialog,
        public IMappingToolWindow
#ifdef USE_INVOKER
        ,public Common::Invoker
#endif
{
    Q_OBJECT
private:
    Ui::MappingToolWindow widget;

    QMenuBar*   m_MenuBar;
    QMenu*      m_FileMenu, *m_ToolsMenu;

    QIrrControlPtr    m_IrrControl;

	std::string m_FastEditorStr;
	int			m_FastEditorRowIndex;
protected:
    //void resizeEvent(QResizeEvent *);
public:
    MappingToolWindow(QWidget* parent = nullptr);
    ~MappingToolWindow();

    virtual void ShowView();
    virtual void HideView();

    virtual const char* DebugName() const;

    virtual IIrrControlPtr GetControl();

    virtual void RefreshSpriteInfo(SpriteTexturesListConstPtr textures, SpriteFramesListConstPtr frames);
	virtual void SetFrameDataChangingError(bool isSetError = false);
	virtual void SetCursor(int cursor);

private Q_SLOTS:
    void OnOpenFileSelected();
    void OnSaveFile();
    void OnOpenTextureSelected();
	void OnFrameSelected(QModelIndex index);
	void OnShowAllChanged();
	void OnTextureSelected(QModelIndex index);
	void OnFrameDataChanged(QStandardItem* item);
	void OnSplitterMoved(int, int);
    void closeEvent (QCloseEvent * ev);
    void resizeEvent(QResizeEvent *evt);
	void keyPressEvent(QKeyEvent *event);
    void DelayedUpdate();

	void MakeFastEditString(QModelIndex index);
	void OnFastEditorChanged(QString text);
	void OnFastEditorCursorPositionChanged(int x, int y);

	void OnShowMapContextMenu(const QPoint& pos);
	void OnCurrentViewChanged(int tabIndex);
} ;

#endif	/* _MAPPINGTOOLWINDOW_H */
