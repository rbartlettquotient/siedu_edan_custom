<?php
/**
 * @file
 * Display Suite article layout configuration.
 */

function ds_teaser() {
  return array(
    'label' => t('Teaser'),
    'regions' => array(
      'media' => t('Media Wrapper'),
      'teaser_content' => t('Content'),
      'link_field' => t('Link Field')
    ),
  );
}
