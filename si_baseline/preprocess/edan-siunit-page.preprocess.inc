<?php


/**
 * Imprementation hook_preprocess_edan_location_page
 */

function si_baseline_preprocess_edan_siunit_page(&$vars) {

  drupal_set_title(t('@location', array('@location' => $vars['title'])));
  $content = $vars['content'];
  $rendered_image = '';
  if(isset($content['images'])) {
    $image = current($content['images']);
//    dpm($image['content']);
//    dpm($image['extended']['alt_text']);
    $image_info = array(
      'src' => $image['content'],
      'alt' => isset($image['extended']['alt_text']) ? $image['extended']['alt_text'] : ''
    );
    $rendered_image = '<img' . drupal_attributes($image_info) . ' />';

  }
  $vars['rendered_image'] = $rendered_image;
  $edit_link = '';
  if(user_access('edit edan si-unit content')) {
    $edit_link = l(t('Edit @title', array('@title' => $vars['title'])), $vars['edit_link'], array('attributes' => array('class' => array('btn'))));
  }
  $vars['edit_link'] = $edit_link;

  if (isset($content['record_link'])) {
    $parsed = parse_url($content['record_link']);
    $vars['content']['record_link'] = l($parsed['host'], $content['record_link']);
  }
  //dpm($vars);
}

