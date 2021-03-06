<?php

/**
 * @file
 * Defines a simple 2-column grid layout.
 */

// Plugin definition.
$plugin = array(
  'title' => t('Two column right'),
  'icon' => 'preview.png',
  'category' => t('Columns: 2'),
  'theme' => 'two_col_right',
  'css' => '../../../css/panels.layout.css',
  'regions' => array(
    'hero' => t('Hero Content'),
    'main_content' => t('Main Content'),
    'right_aside' => t('Right Aside'),
		'bottom' => t('Bottom Content')		
  ),
);

/**
 * Implements hook_preprocess_grid_3().
 */
function template_preprocess_two_col_right(&$variables) {
  $variables['attributes_array']['class'][] = 'panel-display';
  $variables['attributes_array']['class'][] = 'panel-display--two-col';
  $content = $variables['content'];
  $content['mainContent'] = array();
  foreach($variables['content'] as $name => $item) {
    $variables['region_attributes_array'][$name]['class'][] = 'l-region--' . drupal_clean_css_identifier($name);
    if (in_array($name, array('main_content', 'right_aside')) && !empty($item)) {
      $content['mainContent'][$name] = $item;
      switch($name) {
        case 'main_content':
          $variables['region_attributes_array'][$name]['class'][] = 'col';
          if(!empty($variables['content']['right_aside'])) {
            $variables['region_attributes_array'][$name]['class'][] = 'col-md-9';
          }
          else {
            $variables['region_attributes_array'][$name]['class'][] = 'col-12';
          }
          break;
        case 'right_aside':
          $variables['region_attributes_array'][$name]['class'][] = 'col';
          $variables['region_attributes_array'][$name]['class'][] = 'col-md-3';
          $variables['region_attributes_array'][$name]['class'][] = 'last-md';
          break;
      }
    }
  }
  $variables['content'] = $content;
}
