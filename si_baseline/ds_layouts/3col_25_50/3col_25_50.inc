<?php
/**
 * @file
 * Display Suite article layout configuration.
 */

function ds_3col_25_50() {
  return array(
    'label' => t('Three Column - 25/25/50'),
    'regions' => array(
      'header' => t('Header'),
      'left' => t('Left'),
      'middle' => t('Middle'),
      'right' => t('Right'),
    ),
  );
}
