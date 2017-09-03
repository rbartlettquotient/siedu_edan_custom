<?php

/**
 * Implements hook_preprocess_google_appliance_results().
 */
function si_baseline_preprocess_google_appliance_results(&$vars) {
  $vars['search_form'] = '';
  //drupal_add_js(drupal_get_path('theme', 'si_baseline') .'/js/si_search.js', array('scope' => 'footer', 'weight' => 15));
}
