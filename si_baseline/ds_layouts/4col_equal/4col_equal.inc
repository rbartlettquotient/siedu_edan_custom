<?php
/**
 * @file
 * Display Suite article layout configuration.
 */

function ds_4col_equal() {
  return array(
    'label' => t('Four Column Stacked Equal Width'),
    'regions' => array(
      'header' => t('Header'),
      'first' => t('Column 1'),
      'second' => t('Column 2'),
      'third' => t('Column 3'),
      'fourth' => t('Column 4')
    ),
  );
}
