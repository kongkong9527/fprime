// ======================================================================
// \title  ArrayFIFOBuffer.cpp
// \author mereweth
// \brief  ArrayFIFOBuffer implementation
//
// \copyright
// Copyright (C) 2017 California Institute of Technology.
// ALL RIGHTS RESERVED.  United States Government Sponsorship
// acknowledged. Any commercial use must be negotiated with the Office
// of Technology Transfer at the California Institute of Technology.
//
// This software may be subject to U.S. export control laws and
// regulations.  By accepting this document, the user agrees to comply
// with all U.S. export laws and regulations.  User has the
// responsibility to obtain export licenses, or other export authority
// as may be required before exporting such information to foreign
// countries or providing access to foreign persons.
// ======================================================================

#include "Svc/BufferAccumulator/BufferAccumulator.hpp"
#include "Fw/Types/BasicTypes.hpp"

#include "Fw/Types/Assert.hpp"

namespace Svc {

  // ----------------------------------------------------------------------
  // Constructors
  // ----------------------------------------------------------------------

  BufferAccumulator::ArrayFIFOBuffer ::
    ArrayFIFOBuffer(Fw::Buffer *const elements,
                    const NATIVE_UINT_TYPE capacity) :
      elements(elements),
      capacity(capacity),
      enqueueIndex(0),
      dequeueIndex(0),
      size(0)
  {

  }

  // ----------------------------------------------------------------------
  // Public functions
  // ----------------------------------------------------------------------

  bool BufferAccumulator::ArrayFIFOBuffer ::
    enqueue(const Fw::Buffer& e)
  {
    bool status;
    if (this->size < this->capacity) {
      // NOTE(mereweth) enqueueIndex is unsigned, no need to compare with 0
      FW_ASSERT(enqueueIndex < this->capacity, enqueueIndex);
      this->elements[this->enqueueIndex] = e;
      this->enqueueIndex = (this->enqueueIndex + 1) % this->capacity;
      status = true;
      ++this->size;
    }
    else {
      status = false;
    }
    return status;
  }

  bool BufferAccumulator::ArrayFIFOBuffer ::
    dequeue(Fw::Buffer& e)
  {
    bool status;
    if (this->size > 0) {
      // NOTE(mereweth) dequeueIndex is unsigned, no need to compare with 0
      FW_ASSERT(dequeueIndex < this->capacity, enqueueIndex);
      e = this->elements[this->dequeueIndex];
      this->dequeueIndex = (this->dequeueIndex + 1) % this->capacity;
      --this->size;
      status = true;
    }
    else {
      status = false;
    }
    return status;
  }

  U32 BufferAccumulator::ArrayFIFOBuffer ::
    getSize(void) const
  {
    return this->size;
  }

  U32 BufferAccumulator::ArrayFIFOBuffer ::
    getCapacity(void) const
  {
    return this->capacity;
  }

}
