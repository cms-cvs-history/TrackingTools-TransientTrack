#ifndef TrackReco_TrackTransientTrack_h
#define TrackReco_TrackTransientTrack_h
//
// Definition of Transient Track class for 
// reconstruction posterior to track reconstruction (vertexing, b-tagging...)
//

#include "TrackingTools/TransientTrack/interface/BasicTransientTrack.h"
#include "DataFormats/TrackReco/interface/Track.h"
#include "TrackingTools/PatternTools/interface/TSCPBuilderNoMaterial.h"
// #include "TrackingTools/TrajectoryState/interface/TrajectoryStateOnSurface.h"
// #include "TrackingTools/TrajectoryState/interface/FreeTrajectoryState.h"
// #include "TrackingTools/TrajectoryState/interface/TrajectoryStateClosestToPoint.h"
// #include "FWCore/Framework/interface/EventSetup.h"
// #include "FWCore/Framework/interface/ESHandle.h"
// #include "MagneticField/Engine/interface/MagneticField.h"
// #include "Geometry/CommonDetUnit/interface/GlobalTrackingGeometry.h"

namespace reco {

  class TrackTransientTrack : public Track, public BasicTransientTrack {
  public:

    // constructor from persistent track
    TrackTransientTrack(); 
    TrackTransientTrack( const Track & tk , const MagneticField* field); 
    TrackTransientTrack( const TrackRef & tk , const MagneticField* field); 

    TrackTransientTrack( const TrackRef & tk , const MagneticField* field, const edm::ESHandle<GlobalTrackingGeometry>& trackingGeometry);

    TrackTransientTrack( const Track & tk , const MagneticField* field, const edm::ESHandle<GlobalTrackingGeometry>& trackingGeometry);

    TrackTransientTrack( const TrackTransientTrack & tt );
    
    TrackTransientTrack& operator=(const TrackTransientTrack & tt);

    void setES(const edm::EventSetup& );

    void setTrackingGeometry(const edm::ESHandle<GlobalTrackingGeometry>& );

    FreeTrajectoryState initialFreeState() const {return initialFTS;}

    TrajectoryStateOnSurface outermostMeasurementState() const;

    TrajectoryStateOnSurface innermostMeasurementState() const;

    TrajectoryStateClosestToPoint 
      trajectoryStateClosestToPoint( const GlobalPoint & point ) const
      {return builder(initialTSCP.theState(), point);}

   /**
    * The TSOS at any point. The initial state will be used for the propagation.
    */
    TrajectoryStateOnSurface stateOnSurface(const GlobalPoint & point) const;

    TrajectoryStateClosestToPoint impactPointTSCP() const;

    TrajectoryStateOnSurface impactPointState() const;

    bool impactPointStateAvailable() const {return  initialTSOSAvailable;}

    // access to original persistent track
    //    const Track & persistentTrack() const { return *tk_; }
    TrackRef persistentTrackRef() const { return tkr_; }

    TrackCharge charge() const {return Track::charge();}

//     bool operator== (const TransientTrack & a) const {return (a.persistentTrackRef()==tkr_);}
//     bool operator< (const TransientTrack & a) const 
//       {return (initialFTS.momentum().z()<a.initialFreeState().momentum().z());}

    const MagneticField* field() const {return theField;}


  private:

    void calculateTSOSAtVertex() const;

    TrackRef tkr_;
    const MagneticField* theField;

    FreeTrajectoryState initialFTS;
    mutable bool initialTSOSAvailable, initialTSCPAvailable;
    mutable TrajectoryStateOnSurface initialTSOS;
    mutable TrajectoryStateClosestToPoint initialTSCP;
    TSCPBuilderNoMaterial builder;
    edm::ESHandle<GlobalTrackingGeometry> theTrackingGeometry;

  };

}

#endif