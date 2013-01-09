
boost::signals::connection	EdMainWndView::AttachOnNewLevelSelected(const OnNewLevelSelectedSignal::slot_type& slot)
{
    return m_OnNewLevelSignal.connect(slot);
}

boost::signals::connection EdMainWndView::AttachOnSaveLevelSignal( const OnSaveLevelSignal::slot_type& slot )
{
    return m_OnSaveLevelSignal.connect(slot);
}

boost::signals::connection EdMainWndView::AttachOnExitSelected( const OnExitSelectedSignal::slot_type& slot )
{
    return m_OnExitSelectedSignal.connect(slot);
}

boost::signals::connection EdMainWndView::AttachOnAtlasToolsSelectedSignal( const OnAtlasToolsSelectedSignal::slot_type& slot )
{
    return m_OnAtlasToolsSelectedSignal.connect(slot);
}

boost::signals::connection EdMainWndView::AttachOnOpenSelected( const OnOpenSelectedSignal::slot_type& slot )
{
    return m_OnOpenSelectedSignal.connect(slot);
}

boost::signals::connection EdMainWndView::AttachOnMappingSelectedSignal( const OnMappingSelectedSignal::slot_type& slot )
{
    return m_OnMappingSelectedSignal.connect(slot);
}

boost::signals::connection EdMainWndView::AttachOnNewPageSelected( const OnNewPageSelectedSignal::slot_type& slot )
{
    return m_OnNewPageSelectedSignal.connect(slot);
}

boost::signals::connection EdMainWndView::AttachOnLoadMappingFileSignal( const OnLoadMappingFile::slot_type& slot )
{
    return m_OnLoadMappingFile.connect(slot);
}

boost::signals::connection EdMainWndView::AttachOnOnTreeItemSelectedSignal( const OnTreeItemSelectedSignal::slot_type& slot )
{
    return m_OnTreeItemSelectedSignal.connect(slot);
}

boost::signals::connection EdMainWndView::AttachOnAddNewStaticObjectSignal( const OnAddNewObjectSignal::slot_type& slot )
{
    return m_OnAddNewStaticObjectSignal.connect(slot);
}

boost::signals::connection EdMainWndView::AttachOnAddNewAnimatedObjectSignal( const OnAddNewObjectSignal::slot_type& slot )
{
    return m_OnAddNewAnimatedObjectSignal.connect(slot);
}

boost::signals::connection EdMainWndView::AttachOnGameObjectSelectedSignal( const OnGameObjectSelectedSignal::slot_type& slot )
{
    return m_OnGameObjectSelectedSignal.connect(slot);
}

boost::signals::connection EdMainWndView::AttachOnGameObjectPropertySelectedSignal( const OnGameObjectPropertySelectedSignal::slot_type& slot )
{
    return m_OnGameObjectPropertySelectedSignal.connect(slot);
}

boost::signals::connection EdMainWndView::AttachOnLoadLevelSignal( const OnLoadLevelSignal::slot_type& slot )
{
    return m_OnLoadLevelSignal.connect(slot);
}

