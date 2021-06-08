#pragma once


namespace music
{


   namespace midi_core_midi
   {

      class CLASS_DECL_VERIWELL_MULTIMEDIA_MUSIC_MIDI_CORE_MIDI file :
         virtual public ::music::midi::file::buffer
      {
      public:


         
         file(sp(::aura::application) papp);
         virtual ~file();
         
         
         /*         double GetTempoShiftRate();
          
          bool IsTrackMute(int32_t iIndex);
          
          void MuteAll(bool bMute = true, int32_t iExcludeTrack = -1);
          
          void MuteTrack(int32_t iIndex, bool bMute = true);
          
          ::music::e_result WorkSeekBegin();
          
          ::music::e_result CalcTkLength();
          
          ::music::e_result CreateTempoMap();
          
          ::multimedia::e_result ImmediatePutTempoChange();
          
          ::music::e_result GetTempoEvent(::music::midi::event & event);
          
          void OnStop();
          
          uint32_t GetImageSize();
          
          LPBYTE GetImage();
          
          ::music::e_result Format0();
          
          ::music::e_result InsertTempoEvent();
          
          ::music::midi::tempo_map_entry * GetTempoMapEntry(const imedia_time & position);
          
          int32_t GetTempoShift();
          
          ::music::e_result SetTempoShift(int32_t iTempoShift);
          
          void ToWorkStorage();
          
          void FromWorkStorage();
          
          int32_t GetKeyShift();
          
          int32_t SetKeyShift(int32_t iKeyShift);
          
          bool IsSoftKaraokeFile(bool bWork = false, stringa * pstra = NULL);
          
          bool IsXFFile();
          
          bool IsTune1000File();
          
          bool IsOpened();
          
          ::music::e_result RebuildIndex();
          
          ::music::e_result WriteHeader(MIDIFILEHDR * lpmfh);
          
          ::music::e_result ChangeEventDelta(::music::midi::event *pEvent, imedia_time tkNewDelta);
          
          ::music::e_result ReplaceSameDeltaEvent(::music::midi::event & pEventNew);
          
          ::music::e_result GetPreviousEvent(::music::midi::event * pPreviousEvent, ::music::midi::event * pEvent);
          
          ::music::e_result SaveFile(const char * lpFilePath);
          
          ::music::e_result WorkWriteXFTracks(stringa & tokena, imedia_time_array & positiona, ::music::xf::info_header & xfinfoheader);
          
          int32_t CalcMelodyTrack(::music::midi::events ** ppEvents, imedia_time_array * pTicks);
          
          int32_t WorkCalcMelodyTrack(::music::midi::events ** ppEvents, imedia_time_array & positiona, int_array & iaTokenLine);
          
          int32_t GetFormat();
          
          ::music::e_result WorkMergeTracks();
          
          ::music::e_result WorkStreamRender(LPMIDIHDR lpmh, imedia_time tkMax, uint32_t cbPrerollNomimalMax);
          
          ::music::e_result WorkGetNextEvent(::music::midi::event * & pevent, imedia_time tkMax, bool bTkMaxInclusive);
          
          ::music::e_result WorkGetNextRawEvent(::music::midi::event * & pevent, imedia_time tkMax, bool bTkMaxInclusive);
          
          ::music::e_result WorkGetNextRawMidiEvent(::music::midi::event * & pevent, imedia_time tkMax, bool bTkMaxInclusive);
          
          ::music::e_result WorkSeek(::imedia_time tkPosition, LPMIDIHDR lpmh);
          
          void delete_contents();
          
          int32_t GetDivision();
          
          imedia_time GetPosition();
          
          void AttachSeekSync(::ikaraoke::events_tracks_v1 * ptracksv1);
          
          bool IsNull();
          
          void WorkSeekEnd();
          
          ::music::e_result OpenFile(::music::midi::file::buffer &file, int32_t openMode);
          
          ::music::e_result OpenFile(::file::stream_buffer & file, int32_t openMode);
          
          ::music::e_result OpenFile(primitive::memory * pmemstorage, int32_t openMode, ::music::e_storage);
          
          ::music::e_result OpenFile(primitive::memory * pmemstorage, ::music::midi::file::e_open eopenmode, ::music::e_storage estorage);
          
          ::music::e_result SaveFile(::file::stream_buffer & file);
          
          ::music::e_result CloseFile();
          
          ::music::e_result GetFileInfo(PSMFFILEINFO psfi);
          
          int_ptr TicksToMillisecs(imedia_time tkOffset);
          
          void TicksToMillisecs(imedia_time_array *pMillisArray, imedia_time_array *pTickArray, int_ptr tkOffset);
          
          void TicksToMillisecs(imedia_time_2darray *p2DMillisArray, imedia_time_2darray * p2DTicksArray, int_ptr tkOffset);
          
          void PositionToTime(imedia_time_2darray  & timea, imedia_time_2darray  & positiona, int_ptr tkOffset);
          
          void PositionToTime(imedia_time_array  & timea, imedia_time_array  & positiona, int_ptr tkOffset);
          
          imedia_time MillisecsToTicks(imedia_time msOffset);
          
          imedia_time PositionToTime(imedia_time msOffset);
          
          imedia_time TimeToPosition(imedia_time msOffset);
          
          void MillisecsToTicks(imedia_time_array * pTickArray, imedia_time_array *pMillisArray, imedia_time msOffset);
          
          void TimeToPosition(imedia_time_array & positiona, imedia_time_array & timea, imedia_time msOffset);
          
          ::music::e_result StreamRender(LPMIDIHDR lpmh, imedia_time tkMax, uint32_t cbPrerollNomimalMax);
          
          ::multimedia::e_result StreamEvent(imedia_time tkDelta, ::music::midi::event * Event, LPMIDIHDR lpmh, imedia_time tkMax, uint32_t cbPrerollNomimalMax);
          
          ::multimedia::e_result StreamEventF1(imedia_time tkDelta, array < ::music::midi::event *, ::music::midi::event * > & eventptra, LPMIDIHDR lpmh, imedia_time tkMax, uint32_t cbPrerollNomimalMax);
          
          ::music::e_result seek(imedia_time tkPosition, LPMIDIHDR lpmh);
          
          ::music::e_result seek(imedia_time tkPosition);
          
          ::music::e_result Build();
          
          ::music::e_result GetNextEvent(::music::midi::event *& pevent, imedia_time tkMax, bool   bTkMaxInclusive);
          
          ::music::e_result GetNextEventTkPosition(imedia_time * pTkPosition, imedia_time tkMax);
          
          void _SyncSeek(imedia_time tkPosition, ::ikaraoke::events_tracks_v1 * ptracksv1);
          
          void _SyncSeek(imedia_time tkPosition);
          
          ::music::e_result InsertParmData(imedia_time tkDelta, LPMIDIHDR lpmh);
          
          ::multimedia::e_result InsertLyricEvents(::ikaraoke::lyric_event_v1 * pLyricEvent, LPMIDIHDR lpmh);
          
          ::music::e_result InsertPadEvent(imedia_time tkDelta, LPMIDIHDR lpmh);
          
          void SetOpened(bool bOpened = true);
          */
         

      };


   } // namespace midi_core_midi


} // namespace music





