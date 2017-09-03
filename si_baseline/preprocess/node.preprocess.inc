<?php

/**
 * @file
 * Contains a pre-process hook for 'html'.
 */

/**
 * Implements hook_preprocess_node().
 */
function si_baseline_preprocess_node(&$vars) {
  $node = $vars['node'];
//  if ($node->type == 'movie') {
//    $scripts = array();
//    $js = FALSE;
//    $js_path = drupal_get_path('theme', 'si_baseline') .'/js/';
//    $vars['embed_url'] = '';
//    $vars['player_path'] = file_create_url($js_path .'player.swf');
//    if (!empty($node->field_video)) {
//      $file = current($node->field_video['und']);
//      $file_path = file_create_url($file['uri']);
//      $var['embed_url'] = array(
//        'path' => $file_path,
//        'title' => isset($file['description'])
//      );
//    }
//    elseif (!empty($node->field_url)) {
//
//    }
//   // $javascript = drupal_add_js();
//   // dpm($javascript);
//    if ($js) {
//      drupal_add_js( $js_path .'jwplayer.js');
//
//    }
//  }
}

