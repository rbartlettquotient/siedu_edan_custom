<?php
/**
 * @file
 * Display Suite article layout configuration.
 */

function ds_content_wrapper() {
  return array(
    'label' => t('Content Wrapper'),
    'regions' => array(
      'header' => t('Header'),
      'main_content' => t('Content'),
    ),
  );
}
