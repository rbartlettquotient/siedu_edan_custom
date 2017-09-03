<?php

/**
 * Implements hook_preprocess_ogmt_object_group_page().
 */

function si_baseline_preprocess_ogmt_object_group_page(&$vars) {

  $parent_title = '';
  $vars['back_link'] = '';
  $params = drupal_get_query_parameters();
  $dest = isset($params['destination']) ? $params['destination'] : '';
  if (!empty($dest)) {
    $url = drupal_parse_url($dest);
    $link_text = '<span class="fa fa-angle-double-left" aria-hidden="true"></span>' .t('Previous Page');

    $vars['back_link'] = l($link_text, $url['path'], array(
      'query' => $url['query'],
      'fragment' => $url['fragment'],
      'html' => TRUE,
    ));
  }

  if (isset($vars['menu_array']['children'])) {
    $parent_title  = trim(strtolower($vars['objectgroup_title'])) != trim(strtolower($vars['title'])) ? $vars['objectgroup_title'] : '';

    if(!empty($vars['unit_info']) && in_array('NMAH', $vars['unit_info']['content']['unit_codes'])) {
      $vars['menu_array'] = $vars['menu_array']['children'];

    }
    else {
      $menu_array = array_merge(array($vars['menu_array']['parent']), $vars['menu_array']['children']);
      $vars['menu_array'] = $menu_array;
    }
  }
  $vars['parent_title'] = $parent_title;
  if($vars['is_external'] && !empty($vars['unit_info'])) {
    //$unit_classes = array('unit-info', 'pane-node-field-tagline', 'flex-column');
    $unit_classes = array('unit-info', 'pane-node-field-tagline');
    if(!empty($vars['unit_info']['content']['unit_codes'])) {
      foreach ($vars['unit_info']['content']['unit_codes'] as $unit_code) {
        $unit_classes[] = 'has-unit-code';
        $unit_classes[] = drupal_html_class($unit_code);
      }
    }
    if (!empty($vars['unit_info']['#title_plain'])) {
      $unit_classes[] = drupal_html_class($vars['unit_info']['#title_plain']);
      $vars['unit_link'] = !empty($vars['unit_info']['#title_link']) ?
        l(t($vars['unit_info']['#title_plain']), $vars['unit_info']['#title_link']['path'], array('attributes'=> array('class' => array('delta'), 'target' => '_blank'))) : '';

    }
    $unit_classes = implode(' ', $unit_classes);
    $vars['unit_class'] = $unit_classes;

  }
  else {
    $vars['unit_link'] = '';
  }
//  if (strlen($vars['feature_image_ur']) > 1) {
//    drupal_add_html_head(array(
//
//    ), 'ogmt_twitter_image');
//  }

  if(isset($_GET['dpm-ogmt'])) {
    dpm($vars);
  }

}
