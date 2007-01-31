#ifndef TrackReco_BasicTransientTrack_h
#define TrackReco_BasicTransientTrack_h
//
// Definition of Transient Track class for 
// reconstruction posterior to track reconstruction (vertexing, b-tagging...)
//

#include "TrackingTools/TrajectoryState/interface/ProxyBase.h"
#include "Geometry/Surface/interface/ReferenceCounted.h"
#include "TrackingTools/TrajectoryState/interface/CopyUsingClone.h"

// #include "DataFormats/TrackReco/interface/Track.h"
#include "TrackingTools/TrajectoryState/interface/TrajectoryStateOnSurface.h"
#include "TrackingTools/TrajectoryState/interface/FreeTrajectoryState.h"
#include "TrackingTools/TrajectoryState/interface/TrajectoryStateClosestToPoint.h"
#include "FWCore/Framework/interface/EventSetup.h"
#include "FWCore/Framework/interface/ESHandle.h"
#include "Geometry/CommonDetUnit/interface/GlobalTrackingGeometry.h"

// class TransientTrack;

namespace reco {

  class BasicTransientTrack : private ReferenceCounted {
  public:

    typedef BasicTransientTrack                              BTT;
    typedef ProxyBase< BTT, CopyUsingClone<BTT> >        Proxy;
    typedef ReferenceCountingPointer<BasicTransientTrack>    RCPtr;

  private:
    friend class ProxyBase< BTT, CopyUsingClone<BTT> >;
    friend class ReferenceCountingPointer<BasicTransientTrack>;

  public:

    virtual ~BasicTransientTrack() {}

    virtual void setES(const edm::EventSetup& es) = 0;

    virtual void setTrackingGeometry(const edm::ESHandle<GlobalTrackingGeometry>& tg) = 0;

    virtual FreeTrajectoryState initialFreeState() const = 0;

    virtual TrajectoryStateOnSurface outermostMeasurementState() const = 0;

    virtual TrajectoryStateOnSurface innermostMeasurementState() const = 0;

    virtual TrajectoryStateClosestToPoint 
      trajectoryStateClosestToPoint( const GlobalPoint & point ) const = 0;

    virtual TrajectoryStateOnSurface stateOnSurface(const GlobalPoint & point) const = 0;

    virtual TrajectoryStateClosestToPoint impactPointTSCP() const = 0;

    virtual TrajectoryStateOnSurface impactPointState() const = 0;
    virtual bool impactPointStateAvailable() const = 0;

//     TrackRef persistentTrackRef() const { return tkr_; }

    virtual TrackCharge charge() const = 0;

//     virtual bool operator== (const TransientTrack & a) const = 0;
//     virtual bool operator< (const TransientTrack & a) const = 0;

    virtual const MagneticField* field() const = 0;

  };

}

#endif
