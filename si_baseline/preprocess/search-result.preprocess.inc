<?php

/**
 * Implements hook_preprocess_page().
 */
function si_baseline_preprocess_search_result(&$vars) {
  $url = $vars['url'];
  $query['width'] = '85%';
  $query['height'] = '85%';
  $query['iframe'] = 'true';
  $link =  drupal_parse_url($vars['url']);
  $query = array_merge($query, $link['query']);
  $vars['rendered_path'] = url($link['path'], array('fragment' => $link['fragment'], 'query' => $query));

}
