// Copyright (c) 2012 The Chromium Authors. All rights reserved.
// Use of this source code is governed by a BSD-style license that can be
// found in the LICENSE file.

#ifndef UI_VIEWS_EXAMPLES_SLIDER_EXAMPLE_H_
#define UI_VIEWS_EXAMPLES_SLIDER_EXAMPLE_H_
#pragma once

#include "base/basictypes.h"
#include "base/compiler_specific.h"
#include "ui/views/controls/slider.h"
#include "ui/views/examples/example_base.h"

namespace views {
class Label;

namespace examples {

class SliderExample : public ExampleBase, public SliderListener {
 public:
  SliderExample();
  virtual ~SliderExample();

  // Overridden from ExampleBase:
  virtual void CreateExampleView(View* container) OVERRIDE;

 private:
  // Overridden from SliderListener:
  virtual void SliderValueChanged(Slider* sender,
                                  float value,
                                  float old_value,
                                  views::SliderChangeReason reason) OVERRIDE;

  Slider* slider_;
  Label* label_;

  DISALLOW_COPY_AND_ASSIGN(SliderExample);
};

}  // namespace examples
}  // namespace views

#endif  // UI_VIEWS_EXAMPLES_SLIDER_EXAMPLE_H_
