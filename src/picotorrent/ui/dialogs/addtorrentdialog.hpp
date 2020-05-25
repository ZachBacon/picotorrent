#pragma once

#include <wx/wxprec.h>
#ifndef WX_PRECOMP
#include <wx/wx.h>
#endif

#include <libtorrent/download_priority.hpp>
#include <libtorrent/fwd.hpp>
#include <memory>
#include <vector>

class wxChoice;
class wxDataViewCtrl;
class wxDataViewEvent;
class wxDataViewItemArray;

namespace pt
{
namespace Core
{
    class Database;
}
namespace UI
{
namespace Models
{
    class FileStorageModel;
}
namespace Dialogs
{
    class AddTorrentDialog : public wxDialog
    {
    public:
        AddTorrentDialog(wxWindow* parent, wxWindowID id, std::vector<libtorrent::add_torrent_params>& params, std::shared_ptr<Core::Database> db);
        virtual ~AddTorrentDialog();

        std::vector<libtorrent::add_torrent_params> GetTorrentParams() { return m_params; };
        void MetadataFound(std::shared_ptr<libtorrent::torrent_info> const& ti);

    private:
        enum
        {
            ptID_TORRENTS_COMBO = wxID_HIGHEST + 1,
            ptID_SAVE_PATH_INPUT,
            ptID_SAVE_PATH_BROWSE,
            ptID_FILE_LIST,

            ptID_CONTEXT_MENU_DO_NOT_DOWNLOAD,
            ptID_CONTEXT_MENU_LOW,
            ptID_CONTEXT_MENU_NORMAL,
            ptID_CONTEXT_MENU_MAXIMUM,
        };

        wxString GetTorrentDisplayName(libtorrent::add_torrent_params const& params);
        wxString GetTorrentDisplaySize(libtorrent::add_torrent_params const& params);
        wxString GetTorrentDisplayInfoHash(libtorrent::add_torrent_params const& params);
        wxString GetTorrentDisplayComment(libtorrent::add_torrent_params const& params);

        void Load(size_t index);
        void SetFilePriorities(wxDataViewItemArray& items, libtorrent::download_priority_t prio);
        void ShowFileContextMenu(wxDataViewEvent&);

        wxChoice* m_torrents;
        wxStaticText* m_torrentName;
        wxStaticText* m_torrentSize;
        wxStaticText* m_torrentInfoHash;
        wxStaticText* m_torrentComment;
        wxComboBox* m_torrentSavePath;
        wxButton* m_torrentSavePathBrowse;
        wxDataViewCtrl* m_filesView;

        Models::FileStorageModel* m_filesModel;

        std::shared_ptr<Core::Database> m_db;
        std::vector<libtorrent::add_torrent_params> m_params;
    };
}
}
}
