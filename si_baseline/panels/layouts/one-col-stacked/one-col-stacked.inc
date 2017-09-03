<?php

/**
 * @file
 * Defines a simple 2-column grid layout.
 */

// Plugin definition.
$plugin = array(
  'title' => t('One column, stacked'),
  'icon' => 'preview.png',
  'category' => t('Columns: 1'),
  'theme' => 'one_col_stacked',
  'css' => '../../../css/layouts/panels/panels.layout.css',
  'regions' => array(
    'hero' => t('Hero'),
    'main_content' => t('main'),
  ),
);

/**
 * Implements hook_preprocess_grid_3().
 */
function template_preprocess_one_col_stacked(&$variables) {
  $variables['attributes_array']['class'][] = 'panel-display';
  $variables['attributes_array']['class'][] = 'panel-display--one-col-stacked';

  foreach($variables['content'] as $name => $item) {
    $class =  $name == 'hero' ? 'row-1' : 'row-2';
    $variables['region_attributes_array'][$name]['class'][] = $class;
    if ($name == 'hero' && !empty($variables['content']['main_content'])) {
      $variables['region_attributes_array'][$name]['class'][] = 'has-other-content';
    }
   // $variables['region_attributes_array'][$name]['class'][] = $name == 'main_content' ? 'l-container' : '';

  }

}
