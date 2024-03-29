// Copyright (c) 2012 The Chromium Authors. All rights reserved.
// Use of this source code is governed by a BSD-style license that can be
// found in the LICENSE file.

#include "ui/aura/single_monitor_manager.h"

#include <string>

#include "base/command_line.h"
#include "ui/aura/aura_switches.h"
#include "ui/aura/root_window.h"
#include "ui/aura/root_window_host.h"
#include "ui/gfx/display.h"
#include "ui/gfx/rect.h"

namespace aura {

using std::string;

namespace {
// Default bounds for the primary monitor.
const int kDefaultHostWindowX = 200;
const int kDefaultHostWindowY = 200;
const int kDefaultHostWindowWidth = 1280;
const int kDefaultHostWindowHeight = 1024;
}  // namespace

SingleMonitorManager::SingleMonitorManager()
    : root_window_(NULL) {
  Init();
}

SingleMonitorManager::~SingleMonitorManager() {
  // All monitors must have been deleted when monitor manager is deleted.
  CHECK(!root_window_);
}

void SingleMonitorManager::OnNativeMonitorsChanged(
    const std::vector<gfx::Display>& displays) {
  DCHECK(displays.size() > 0);
  if (use_fullscreen_host_window()) {
    display_.SetSize(displays[0].bounds().size());
    NotifyBoundsChanged(display_);
  }
}

RootWindow* SingleMonitorManager::CreateRootWindowForMonitor(
    const gfx::Display& display) {
  DCHECK(!root_window_);
  DCHECK_EQ(display_.id(), display.id());
  root_window_ = new RootWindow(display.bounds());
  root_window_->AddObserver(this);
  root_window_->Init();
  return root_window_;
}

const gfx::Display& SingleMonitorManager::GetDisplayAt(size_t index) {
  return display_;
}

size_t SingleMonitorManager::GetNumDisplays() const {
  return 1;
}

const gfx::Display& SingleMonitorManager::GetDisplayNearestWindow(
    const Window* window) const {
  return display_;
}

const gfx::Display& SingleMonitorManager::GetDisplayNearestPoint(
    const gfx::Point& point) const {
  return display_;
}

void SingleMonitorManager::OnWindowBoundsChanged(
    Window* window, const gfx::Rect& old_bounds, const gfx::Rect& new_bounds) {
  if (!use_fullscreen_host_window()) {
    Update(new_bounds.size());
    NotifyBoundsChanged(display_);
  }
}

void SingleMonitorManager::OnWindowDestroying(Window* window) {
  if (root_window_ == window)
    root_window_ = NULL;
}

void SingleMonitorManager::Init() {
  const string size_str = CommandLine::ForCurrentProcess()->GetSwitchValueASCII(
      switches::kAuraHostWindowSize);
  display_ = CreateMonitorFromSpec(size_str);
}

void SingleMonitorManager::Update(const gfx::Size size) {
  display_.SetSize(size);
}

}  // namespace aura
