// Aseprite Document Library
// Copyright (c) 2001-2015 David Capello
//
// This file is released under the terms of the MIT license.
// Read LICENSE.txt for more information.

#ifdef HAVE_CONFIG_H
#include "config.h"
#endif

#include "doc/frame_tag_io.h"

#include "base/serialization.h"
#include "base/unique_ptr.h"
#include "doc/frame_tag.h"
#include "doc/string_io.h"

#include <iostream>

namespace doc {

using namespace base::serialization;
using namespace base::serialization::little_endian;

void write_frame_tag(std::ostream& os, FrameTag* tag)
{
  std::string name = tag->name();

  write32(os, tag->id());
  write32(os, tag->fromFrame());
  write32(os, tag->toFrame());
  write32(os, tag->color());
  write_string(os, tag->name());
}

FrameTag* read_frame_tag(std::istream& is)
{
  ObjectId id = read32(is);
  frame_t from = read32(is);
  frame_t to = read32(is);
  color_t color = read32(is);
  std::string name = read_string(is);

  base::UniquePtr<FrameTag> tag(new FrameTag(from, to));
  tag->setColor(color);
  tag->setName(name);
  tag->setId(id);
  return tag.release();
}

}
