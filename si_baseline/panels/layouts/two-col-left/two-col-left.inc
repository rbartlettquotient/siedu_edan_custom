<?php

/**
 * @file
 * Defines a simple 2-column grid layout.
 */

// Plugin definition.
$plugin = array(
  'title' => t('Two column left'),
  'icon' => 'preview.png',
  'category' => t('Columns: 2'),
  'theme' => 'two_col_left',
  'css' => '../../../css/panels.layout.css',
  'regions' => array(
    'hero' => t('Hero Content'),
    'main_content' => t('Main Content'),
    'left_aside' => t('Left Aside'),
		'bottom' => t('Bottom Content')
  ),
);

/**
 * Implements hook_preprocess_grid_3().
 */
function template_preprocess_two_col_left(&$variables) {
  $variables['attributes_array']['class'][] = 'panel-display';
  $variables['attributes_array']['class'][] = 'panel-display--two-col';
  $content = $variables['content'];
  $content['mainContent'] = array();
  foreach($variables['content'] as $name => $item) {
    $variables['region_attributes_array'][$name]['class'][] = 'l-region--' . drupal_clean_css_identifier($name);
    if (in_array($name, array('main_content', 'left_aside')) && !empty($item)) {
      $content['mainContent'][$name] = $item;
      switch($name) {
        case 'main_content':
          $variables['region_attributes_array'][$name]['class'][] = 'col';
          if(!empty($variables['content']['left_aside'])) {
            $variables['region_attributes_array'][$name]['class'][] = 'col-md-9';
            $variables['region_attributes_array'][$name]['class'][] = 'last-md';
          }
          else {
            $variables['region_attributes_array'][$name]['class'][] = 'col-12';
          }
          break;
        case 'left_aside':
          $variables['region_attributes_array'][$name]['class'][] = 'col';
          $variables['region_attributes_array'][$name]['class'][] = 'col-md-3';
          break;
      }
    }
  }
  $variables['content'] = $content;
}
