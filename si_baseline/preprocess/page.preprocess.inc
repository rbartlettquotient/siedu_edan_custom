<?php

/**
 * Implements hook_preprocess_page().
 */
function si_baseline_preprocess_page(&$vars) {
	$path = drupal_get_path('theme', 'si_baseline');
	$vars['logo_icon'] = '';
	$filename =  $path . '/logo-icon.png';
	if (file_exists($filename)) {
		$vars['logo_icon'] = file_create_url($filename);
	}
//	if(arg(0) == 'exhibitions') {
//    $vars['theme_hook_suggestions'][] = 'page__exhibitions';
//  }
//  dpm($vars);
 // drupal_add_js($path .'/js/iframeResizer.min.js', array('scope' => 'footer'));
 // drupal_add_js($path .'/js/iframe.js', array('scope' => 'footer'));
//dpm($vars);
  if (!empty($vars['page']['header_preface_left'])) {
    drupal_add_js($path .'/js/jquery.marquee.min.js', array('weight' => -100));
  }
  $vars['classes_array'][] = 'wrapper--page';
  $class = $vars['classes_array'];
  $vars['attributes_array']['class'] =  $class;
  libraries_load('imagesloaded');
  drupal_add_js(drupal_get_path('theme', 'si_baseline') .'/js/si_search.js', array('scope' => 'footer'));


}
