/* -----------------------------------------------------------------------------
 * Copyright 2017, Massachusetts Institute of Technology,
 * Cambridge, MA 02139
 * All Rights Reserved
 * Authors: Luca Carlone, et al. (see THANKS for the full author list)
 * See LICENSE for the license information
 * -------------------------------------------------------------------------- */

/**
 * @file   testVioFrontEndParams.h
 * @brief  test VioFrontEndParams
 * @author Antoni Rosinol, Luca Carlone
 */

#include <algorithm>
#include <cstdlib>
#include <iostream>
#include <random>
#include "CameraParams.h"
#include "Frame.h"
#include "VioFrontEndParams.h"

#include <gflags/gflags.h>
#include <glog/logging.h>
#include <gtest/gtest.h>

DECLARE_string(test_data_path);

using namespace gtsam;
using namespace std;
using namespace VIO;

static const double tol = 1e-7;

/* ************************************************************************* */
TEST(testTracker, TrackerParamParseYAML) {
  // check that YAML is parsed correctly

  // Test parseYAML
  VioFrontEndParams tp;
  tp.parseYAML(string(FLAGS_test_data_path) +
               "/ForTracker/trackerParameters.yaml");

  // Compare results!
  EXPECT(tp.klt_win_size_ == 24);
  EXPECT(tp.klt_max_iter_ == 30);
  EXPECT(tp.klt_max_level_ == 2);
  EXPECT(tp.klt_eps_ == 0.001);
  EXPECT(tp.maxFeatureAge_ == 10);

  EXPECT(tp.maxFeaturesPerFrame_ == 200);
  EXPECT(tp.quality_level_ == 0.5);
  EXPECT(tp.min_distance_ == 20);
  EXPECT(tp.block_size_ == 3);
  EXPECT(tp.use_harris_detector_ == 0);
  EXPECT(tp.k_ == 0.04);

  EXPECT(tp.stereo_matching_params_.equalize_image_ == true);
  EXPECT(tp.stereo_matching_params_.nominal_baseline_ == 110);
  EXPECT(tp.stereo_matching_params_.tolerance_template_matching_ == 0.17);
  EXPECT(tp.stereo_matching_params_.templ_cols_ == 103);
  EXPECT(tp.stereo_matching_params_.templ_rows_ == 5);
  EXPECT(tp.stereo_matching_params_.stripe_extra_rows_ == 2);
  EXPECT(tp.stereo_matching_params_.min_point_dist_ == 0.1);
  EXPECT(tp.stereo_matching_params_.max_point_dist_ == 150);
  EXPECT(tp.stereo_matching_params_.bidirectional_matching_ == true);
  EXPECT(tp.stereo_matching_params_.subpixel_refinement_ == true);

  EXPECT(tp.featureSelectionCriterion_ == 2);
  EXPECT(tp.featureSelectionHorizon_ == 1);
  EXPECT(tp.featureSelectionNrCornersToSelect_ == 10);
  EXPECT(tp.featureSelectionImuRate_ == 0.001);
  EXPECT(tp.featureSelectionDefaultDepth_ == 4);
  EXPECT(tp.featureSelectionCosineNeighborhood_ == 0.9);
  EXPECT(tp.featureSelectionUseLazyEvaluation_ == 0);
  EXPECT(tp.useSuccessProbabilities_ == 0);

  EXPECT(tp.useRANSAC_ == false);
  EXPECT(tp.minNrMonoInliers_ == 2000);
  EXPECT(tp.minNrStereoInliers_ == 1000);
  EXPECT(tp.ransac_threshold_mono_ == 1e-06);
  EXPECT(tp.ransac_threshold_stereo_ == 0.3);
  EXPECT(tp.ransac_use_1point_stereo_ == false);
  EXPECT(tp.ransac_use_2point_mono_ == true);
  EXPECT(tp.ransac_max_iterations_ == 100);
  EXPECT(tp.ransac_probability_ == 0.995);
  EXPECT(tp.ransac_randomize_ == false);

  EXPECT(tp.intra_keyframe_time_ == 0.5);
  EXPECT(tp.min_number_features_ == 100);
  EXPECT(tp.useStereoTracking_ == 1);
  EXPECT(tp.display_time_ == 100);
  EXPECT(tp.disparityThreshold_ == 1);
}

/* ************************************************************************** */
TEST(testTracker, equals) {
  VioFrontEndParams tp = VioFrontEndParams();
  EXPECT(tp.equals(tp));

  VioFrontEndParams tp2 = VioFrontEndParams();
  tp2.featureSelectionCosineNeighborhood_ += 1e-7;  // small perturbation

  EXPECT(!tp.equals(tp2));
}

/* ************************************************************************** *
TEST(testTracker, cppVSmatlabVioFrontEndParams) {
  // check that the cpp default params match the matlab ones.
  // before running, make sure that you run "writeDefaultParams" in matlab
  VioFrontEndParams cppDefault_tp = VioFrontEndParams();

  VioFrontEndParams matlabDefault_tp;
  matlabDefault_tp.parseYAML(string(FLAGS_test_data_path) +
"/../../matlab/myLib/defaultTrackerParams.yaml");

  EXPECT(matlabDefault_tp.equals(cppDefault_tp));

  if(!matlabDefault_tp.equals(cppDefault_tp)){
    matlabDefault_tp.print();
    cppDefault_tp.print();
  }
}

/* ************************************************************************** */
int main() {
  TestResult tr;
  return TestRegistry::runAllTests(tr);
}
/* ************************************************************************** */
