/* -*- Mode: C++; tab-width: 2; indent-tabs-mode: nil; c-basic-offset: 2 -*- */
/* ***** BEGIN LICENSE BLOCK *****
 * Version: MPL 1.1/GPL 2.0/LGPL 2.1
 *
 * The contents of this file are subject to the Mozilla Public License Version
 * 1.1 (the "License"); you may not use this file except in compliance with
 * the License. You may obtain a copy of the License at
 * http://www.mozilla.org/MPL/
 *
 * Software distributed under the License is distributed on an "AS IS" basis,
 * WITHOUT WARRANTY OF ANY KIND, either express or implied. See the License
 * for the specific language governing rights and limitations under the
 * License.
 *
 * The Original Code is the Mozilla SMIL module.
 *
 * The Initial Developer of the Original Code is Brian Birtles.
 * Portions created by the Initial Developer are Copyright (C) 2005
 * the Initial Developer. All Rights Reserved.
 *
 * Contributor(s):
 *   Brian Birtles <birtles@gmail.com>
 *
 * Alternatively, the contents of this file may be used under the terms of
 * either of the GNU General Public License Version 2 or later (the "GPL"),
 * or the GNU Lesser General Public License Version 2.1 or later (the "LGPL"),
 * in which case the provisions of the GPL or the LGPL are applicable instead
 * of those above. If you wish to allow use of your version of this file only
 * under the terms of either the GPL or the LGPL, and not to allow others to
 * use your version of this file under the terms of the MPL, indicate your
 * decision by deleting the provisions above and replace them with the notice
 * and other provisions required by the GPL or the LGPL. If you do not delete
 * the provisions above, a recipient may use your version of this file under
 * the terms of any one of the MPL, the GPL or the LGPL.
 *
 * ***** END LICENSE BLOCK ***** */

#ifndef NS_SMILINSTANCETIME_H_
#define NS_SMILINSTANCETIME_H_

#include "nsSMILTimeValue.h"
#include "nsAutoPtr.h"

class nsSMILInterval;
class nsSMILTimeContainer;
class nsSMILTimeValueSpec;

//----------------------------------------------------------------------
// nsSMILInstanceTime
//
// An instant in document simple time that may be used in creating a new
// interval.
//
// For an overview of how this class is related to other SMIL time classes see
// the documentation in nsSMILTimeValue.h
//
// These objects are owned by an nsSMILTimedElement but MAY also be referenced
// by:
//
// a) nsSMILIntervals that belong to the same nsSMILTimedElement and which refer
//    to the nsSMILInstanceTimes which form the interval endpoints; and/or
// b) nsSMILIntervals that belong to other nsSMILTimedElements but which need to
//    update dependent instance times when they change or are deleted.
//    E.g. for begin='a.begin', 'a' needs to inform dependent
//    nsSMILInstanceTimes if its begin time changes. This notification is
//    performed by the nsSMILInterval.

class nsSMILInstanceTime
{
public:
  // Instance time source. Times generated by events, syncbase relationships,
  // and DOM calls behave differently in some circumstances such as when a timed
  // element is reset.
  enum nsSMILInstanceTimeSource {
    // No particularly significant source, e.g. offset time, 'indefinite'
    SOURCE_NONE,
    // Generated by a DOM call such as beginElement
    SOURCE_DOM,
    // Generated by a syncbase relationship
    SOURCE_SYNCBASE,
    // Generated by an event
    SOURCE_EVENT
  };

  nsSMILInstanceTime(const nsSMILTimeValue& aTime,
                     nsSMILInstanceTimeSource aSource = SOURCE_NONE,
                     nsSMILTimeValueSpec* aCreator = nsnull,
                     nsSMILInterval* aBaseInterval = nsnull);
  ~nsSMILInstanceTime();
  void Unlink();
  void HandleChangedInterval(const nsSMILTimeContainer* aSrcContainer,
                             PRBool aBeginObjectChanged,
                             PRBool aEndObjectChanged);
  void HandleDeletedInterval();

  const nsSMILTimeValue& Time() const { return mTime; }
  const nsSMILTimeValueSpec* GetCreator() const { return mCreator; }

  PRBool ClearOnReset() const { return !!(mFlags & kClearOnReset); }
  PRBool MayUpdate() const { return !!(mFlags & kMayUpdate); }
  PRBool FromDOM() const { return !!(mFlags & kFromDOM); }

  void MarkNoLongerUpdating() { mFlags &= ~kMayUpdate; }

  void DependentUpdate(const nsSMILTimeValue& aNewTime)
  {
    NS_ABORT_IF_FALSE(MayUpdate(),
        "Updating an instance time that is not expected to be updated");
    mTime = aNewTime;
  }

  PRBool IsDependent(const nsSMILInstanceTime& aOther) const;

  PRBool SameTimeAndBase(const nsSMILInstanceTime& aOther) const
  {
    return mTime == aOther.mTime && GetBaseTime() == aOther.GetBaseTime();
  }

  // Get and set a serial number which may be used by a containing class to
  // control the sort order of otherwise similar instance times.
  PRUint32 Serial() const { return mSerial; }
  void SetSerial(PRUint32 aIndex) { mSerial = aIndex; }

  NS_INLINE_DECL_REFCOUNTING(nsSMILInstanceTime)

protected:
  void SetBaseInterval(nsSMILInterval* aBaseInterval);
  const nsSMILInstanceTime* GetBaseTime() const;

  nsSMILTimeValue mTime;

  // Internal flags used to represent the behaviour of different instance times
  enum {
    // Indicates if this instance time should be removed when the owning timed
    // element is reset. True for events and DOM calls.
    kClearOnReset = 1,

    // Indicates that this instance time is referred to by an
    // nsSMILTimeValueSpec and as such may be updated. Such instance time should
    // not be filtered out by the nsSMILTimedElement even if they appear to be
    // in the past as they may be updated to a future time. Initially set for
    // syncbase-generated times until they are frozen.
    kMayUpdate = 2,

    // Indicates that this instance time was generated from the DOM as opposed
    // to an nsSMILTimeValueSpec. When a 'begin' or 'end' attribute is set or
    // reset we should clear all the instance times that have been generated by
    // that attribute (and hence an nsSMILTimeValueSpec), but not those from the
    // DOM.
    kFromDOM = 4
  };
  PRUint8       mFlags; // Combination of kClearOnReset, kMayUpdate, etc.
  PRUint32      mSerial; // A serial number used by the containing class to
                         // specify the sort order for instance times with the
                         // same mTime.
  PRPackedBool  mVisited; // (mutable) Cycle tracking
  PRPackedBool  mChainEnd; // Flag to indicate that this instance time is part
                           // of some cyclic dependency and that in order to
                           // avoid infinite recursion the cycle should not be
                           // followed any further than this point.

  nsSMILTimeValueSpec* mCreator; // The nsSMILTimeValueSpec object that created
                                 // us. (currently only needed for syncbase
                                 // instance times.)
  nsSMILInterval* mBaseInterval; // Interval from which this time is derived
                                 // (only used for syncbase instance times)
};

#endif // NS_SMILINSTANCETIME_H_
