<?php

/**
 * @file
 * Defines a simple 2-column grid layout.
 */

// Plugin definition.
$plugin = array(
  'title' => t('Fluid Four Column, equal'),
  'icon' => 'preview.png',
  'category' => t('Columns: 4'),
  'theme' => 'four_col_equal',
  'css' => '../../../css/layouts/panels/panels.layout.css',
  'regions' => array(
    'col-one' => t('Column 1'),
    'col-two' => t('Column 2'),
    'col-three' => t('Column 3'),
    'col-four' => t('Column 4'),
  ),
);

/**
 * Implements hook_preprocess_grid_3().
 */
function template_preprocess_four_col_equal(&$variables) {
  $variables['attributes_array']['class'][] = 'panel-display';
  $variables['attributes_array']['class'][] = 'layout';

  foreach($variables['content'] as $name => $item) {
    $variables['region_attributes_array'][$name]['class'][] = 'l-region--' . drupal_clean_css_identifier($name);
    $variables['region_attributes_array'][$name]['class'][] = 'col-sm-3';
    $variables['region_attributes_array'][$name]['class'][] = 'col-md-3';
    $variables['region_attributes_array'][$name]['class'][] = $name == 'col-four' ? 'last' : '';
  }

}
