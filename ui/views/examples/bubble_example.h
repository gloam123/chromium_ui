// Copyright (c) 2011 The Chromium Authors. All rights reserved.
// Use of this source code is governed by a BSD-style license that can be
// found in the LICENSE file.

#ifndef UI_VIEWS_EXAMPLES_BUBBLE_EXAMPLE_H_
#define UI_VIEWS_EXAMPLES_BUBBLE_EXAMPLE_H_
#pragma once

#include "ui/views/controls/button/button.h"
#include "base/compiler_specific.h"
#include "ui/views/examples/example_base.h"
#include "ui/views/animation/bounds_animator.h"

namespace content {
class BrowserContext;
}

namespace views {
class WebView;

namespace examples {

// A Bubble example.
class BubbleExample : public ExampleBase, public ButtonListener {
 public:
  BubbleExample();
  BubbleExample(content::BrowserContext* browser_context);
  virtual ~BubbleExample();

  // Overridden from ExampleBase.
  virtual void CreateExampleView(View* container) OVERRIDE;

 private:
  virtual void ButtonPressed(Button* sender, const Event& event) OVERRIDE;

  Button* round_;
  Button* arrow_;
  Button* fade_in_;
  Button* fade_out_;

  //gqg add
  views::BoundsAnimator *bounds_animator_;

  content::BrowserContext* browser_context_;

  DISALLOW_COPY_AND_ASSIGN(BubbleExample);
};

}  // namespace examples
}  // namespace views

#endif  // UI_VIEWS_EXAMPLES_BUBBLE_EXAMPLE_H_
