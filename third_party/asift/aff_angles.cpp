/*M///////////////////////////////////////////////////////////////////////////////////////
//
//  An OpenCV Implementation of affine-covariant matching (matching with different viewpoints)
//  Further Information Refer to:
//  Author: Evgeny Toropov
//  etoropov@andrew.cmu.edu
//
// IMPORTANT: READ BEFORE DOWNLOADING, COPYING, INSTALLING OR USING.
// 
// By downloading, copying, installing or using the software you agree to this license.
// If you do not agree to this license, do not download, install,
// copy or use the software.
// 
// 
//                           License Agreement
//                For Open Source Computer Vision Library
// 
// Copyright (C) 2000-2008, Intel Corporation, all rights reserved.
// Copyright (C) 2008-2013, Willow Garage Inc., all rights reserved.
// Third party copyrights are property of their respective owners.
// 
// Redistribution and use in source and binary forms, with or without modification,
// are permitted provided that the following conditions are met:
// 
//   * Redistributions of source code must retain the above copyright notice,
//     this list of conditions and the following disclaimer.
// 
//   * Redistributions in binary form must reproduce the above copyright notice,
//     this list of conditions and the following disclaimer in the documentation
//     and/or other materials provided with the distribution.
// 
//   * The name of the copyright holders may not be used to endorse or promote products
//     derived from this software without specific prior written permission.
//
// This software is provided by the copyright holders and contributors "as is" and
// any express or implied warranties, including, but not limited to, the implied
// warranties of merchantability and fitness for a particular purpose are disclaimed.
// In no event shall the Intel Corporation or contributors be liable for any direct,
// indirect, incidental, special, exemplary, or consequential damages
// (including, but not limited to, procurement of substitute goods or services;
// loss of use, data, or profits; or business interruption) however caused
// and on any theory of liability, whether in contract, strict liability,
// or tort (including negligence or otherwise) arising in any way out of
// the use of this software, even if advised of the possibility of such damage.
//
//M*/

#include <sstream>
#include <map>
#include <iomanip>
#include <algorithm>

//#include "precomp.hpp"
#include <opencv2/imgproc/imgproc.hpp>

#include "aff_features2d.hpp"


using namespace std;

namespace cv { namespace affma {




class AffAnglesImpl : public AffAngles {
protected:

    // constant settings from asift paper
    static float          Tilts[6];
    static unsigned int   NumRolls[6];
    
    vector< vector<float> > _rolls;              // rolls for every tilt
    vector<float>         _tiltPool, _rollPool;  // all in one vector
    
    void                  formRolls();           // create _rolls
    void                  formPools();           // create _tiltPool, _rollPool
    
    
    unsigned int          _minTilt, _maxTilt;    // control which part of Tilts[] to use
    
private:
    void                  getActiveViewIds (unsigned int* first, unsigned int* last) const;
    
public:
    AffAnglesImpl (unsigned int maxTilt, unsigned int minTilt = 0);
    AffAnglesImpl (const AffAnglesImpl& old);
    virtual ~AffAnglesImpl() { }
    
    
    void                  setMinTilt(unsigned int minTilt)
                                               { CV_Assert (minTilt < MaxPossibleTilt);
                                                 _minTilt = minTilt;
                                               }
    unsigned int          getMinTilt() const   { return _minTilt; }
    void                  setMaxTilt(unsigned int maxTilt)
                                               { CV_Assert (maxTilt <= MaxPossibleTilt);
                                                 _maxTilt = maxTilt;
                                               }
    unsigned int          getMaxTilt() const   { return _maxTilt; }


    unsigned int          getNumViews () const { unsigned int first, last;
                                                 getActiveViewIds (&first, &last);
                                                 return last - first;
                                               }
    unsigned int          getNumTilts () const { return _maxTilt - _minTilt; }
    unsigned int          getNumRolls (unsigned int tilt) const
                                               { CV_Assert (tilt < MaxPossibleTilt);
                                                 return NumRolls[tilt];
                                               }
    
    vector<float>         getActiveTilts() const; // the active subset <= _minTilt, _maxTilt
    vector<float>         getActiveRolls() const; // the active subset <= _minTilt, _maxTilt
    
    void                  printActiveAngles (std::ostream& os) const;
};

Ptr<AffAngles> createAffAngles (unsigned int maxTilt, unsigned int minTilt)
{
    return new AffAnglesImpl (maxTilt, minTilt);
}


float        AffAnglesImpl::Tilts[6] = { 0, 45, 60, 69, 76, 80 };
unsigned int AffAnglesImpl::NumRolls[6] = { 1, 4, 5, 7, 10, 14 };


AffAnglesImpl::AffAnglesImpl (unsigned int maxTilt, unsigned int minTilt)
{
    CV_Assert (maxTilt > minTilt);

    // create pools of tilt and roll angles
    formRolls();
    formPools();
    
    setMinTilt (minTilt);
    setMaxTilt (maxTilt);
}

AffAnglesImpl::AffAnglesImpl (const AffAnglesImpl& old)
{
    _rolls    = old._rolls;
    _tiltPool = old._tiltPool;
    _rollPool = old._rollPool;
    _minTilt  = old._minTilt;
    _maxTilt  = old._maxTilt;
}

void AffAnglesImpl::formRolls()
{
    _rolls = vector< vector<float> > (MaxPossibleTilt);
    for (int iTilt = 0; iTilt != MaxPossibleTilt; ++iTilt)
    {
        _rolls[iTilt] = vector<float> (NumRolls[iTilt]);
        float roll = 0;
        for (int iRoll = 0; iRoll != NumRolls[iTilt]; ++iRoll)
        {
            _rolls[iTilt][iRoll] = roll;
            roll += 180.f / NumRolls[iTilt];
        }
    }
}

void AffAnglesImpl::formPools()
{
    _tiltPool.clear();
    _rollPool.clear();
    
    for (int iTilt = 0; iTilt != MaxPossibleTilt; ++iTilt)
        for (int iRoll = 0; iRoll != NumRolls[iTilt]; ++iRoll)
        {
            _tiltPool.push_back (Tilts[iTilt]);
            _rollPool.push_back (_rolls[iTilt][iRoll]);
        }
}

void AffAnglesImpl::getActiveViewIds (unsigned int* first, unsigned int* last) const
{
    CV_Assert (_minTilt < _maxTilt);
    CV_Assert (_maxTilt < MaxPossibleTilt);

    // count views till _minTilt and till _maxTilt
    *first = 0, *last = 0;
    for (int iTilt = 0; iTilt != _minTilt; ++iTilt)
        *first += NumRolls[iTilt];
    for (int iTilt = 0; iTilt != _maxTilt; ++iTilt)
        *last  += NumRolls[iTilt];
}

vector<float> AffAnglesImpl::getActiveTilts() const
{
    unsigned int first, last;
    getActiveViewIds (&first, &last);
    return vector<float> (_tiltPool.begin() + first, _tiltPool.begin() + last);
}

vector<float> AffAnglesImpl::getActiveRolls() const
{
    unsigned int first, last;
    getActiveViewIds (&first, &last);
    return vector<float> (_rollPool.begin() + first, _rollPool.begin() + last);
}

void AffAnglesImpl::printActiveAngles (std::ostream& os) const
{
    for (int i = 0; i != _tiltPool.size(); ++i)
        os << "pitch[" << i << "] = " << _tiltPool[i]
           << ", roll[" << i << "] = " << _rollPool[i] << endl;
}


}} // namespaces