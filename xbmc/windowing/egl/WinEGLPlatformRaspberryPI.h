#pragma once
/*
 *      Copyright (C) 2005-2011 Team XBMC
 *      http://www.xbmc.org
 *
 *  This Program is free software; you can redistribute it and/or modify
 *  it under the terms of the GNU General Public License as published by
 *  the Free Software Foundation; either version 2, or (at your option)
 *  any later version.
 *
 *  This Program is distributed in the hope that it will be useful,
 *  but WITHOUT ANY WARRANTY; without even the implied warranty of
 *  MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE. See the
 *  GNU General Public License for more details.
 *
 *  You should have received a copy of the GNU General Public License
 *  along with XBMC; see the file COPYING.  If not, write to
 *  the Free Software Foundation, 675 Mass Ave, Cambridge, MA 02139, USA.
 *  http://www.gnu.org/copyleft/gpl.html
 *
 */

#if defined(TARGET_RASPBERRY_PI)

#include "WinEGLPlatformGeneric.h"
#include "utils/StringUtils.h"
#include "guilib/Resolution.h"

#include <semaphore.h>

#include "linux/DllBCM.h"

class CWinEGLPlatformRaspberryPI
{
public:
  CWinEGLPlatformRaspberryPI();
  virtual ~CWinEGLPlatformRaspberryPI();

  virtual EGLNativeWindowType InitWindowSystem(EGLNativeDisplayType nativeDisplay, int width, int height, int bpp);
  virtual void DestroyWindowSystem(EGLNativeWindowType native_window);
  virtual bool SetDisplayResolution(RESOLUTION_INFO &res);
  virtual bool ClampToGUIDisplayLimits(int &width, int &height);
  virtual bool ProbeDisplayResolutions(std::vector<RESOLUTION_INFO> &resolutions);
  virtual bool CreateSurface();
  virtual bool DestroyWindow();
  virtual bool ShowWindow(bool show);
  virtual bool ReleaseSurface();
  virtual void SwapBuffers();
  virtual bool SetVSync(bool enable);
  virtual bool IsExtSupported(const char* extension);
  virtual EGLDisplay            GetDisplay();
  virtual EGLSurface            GetSurface();
  virtual EGLContext            GetContext();
  virtual bool                  FixedDesktop() { return true; }
  virtual RESOLUTION_INFO       GetDesktopRes() { return m_desktopRes; }

protected:
  virtual bool setConfiguration();
  virtual void createSurfaceCallback() { }

  EGL_DISPMANX_WINDOW_T *m_nativeWindow;
  EGLNativeDisplayType  m_nativeDisplay;
  EGLDisplay            m_display;
  EGLSurface            m_surface;
  EGLConfig             m_config;
  EGLContext            m_context;
  CStdString            m_eglext;
  int                   m_width;
  int                   m_height;

  int                   m_fb_width;
  int                   m_fb_height;
  int                   m_fb_bpp;
  DllBcmHost            m_DllBcmHost;

  DISPMANX_ELEMENT_HANDLE_T m_dispman_element;
  DISPMANX_ELEMENT_HANDLE_T m_dispman_element2;
  DISPMANX_DISPLAY_HANDLE_T m_dispman_display;
  sem_t                 m_tv_synced;

  void GetSupportedModes(HDMI_RES_GROUP_T group, std::vector<RESOLUTION_INFO> &resolutions);
  void TvServiceCallback(uint32_t reason, uint32_t param1, uint32_t param2);
  static void CallbackTvServiceCallback(void *userdata, uint32_t reason, uint32_t param1, uint32_t param2);

  std::vector<RESOLUTION_INFO> m_res;

  RESOLUTION_INFO m_desktopRes;

  TV_GET_STATE_RESP_T m_tv_state;

  bool                  m_sdMode;
};

#endif
