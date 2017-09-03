<?php

/**
 * @file
 * Contains a pre-process hook for 'html'.
 */

/**
 * Implements hook_preprocess_region().
 */
function si_baseline_preprocess_region(&$vars) {
  // Sidebar regions common template suggestion for all sidebars.
  if (strpos($vars['region'], 'footer') === 0) {
    array_unshift($vars['classes_array'], 'l-container');
    // Allow a region-specific template to override region--sidebar.
  }

  //dpm($vars);
}

