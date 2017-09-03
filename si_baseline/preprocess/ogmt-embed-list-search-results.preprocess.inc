<?php

/**
 * Implements hook_preprocess_ogmt_embed_list_search_results().
 */

function si_baseline_preprocess_ogmt_embed_list_search_results(&$vars) {
$docs = $vars['docs'];
  libraries_load('imagesloaded');
  libraries_load('masonry');



}