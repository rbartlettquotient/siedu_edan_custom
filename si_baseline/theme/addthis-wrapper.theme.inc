<?php

/**
 * @file
 * Contains the theme function override for 'menu links'.
 */

/**
 * Returns HTML for a menu link.
 *
 * @ingroup themeable
 */
function si_baseline_addthis_wrapper($variables) {
  $output = '<div class="wrapper--addthis">';
  $output .= '<a href="#" class="share-icon"><span class="sr-only">Share Icon</span></a>  ';
  $element = $variables['addthis_wrapper'];
  $output .= '<' . $element['#tag'] . drupal_attributes($element['#attributes']) . '>';
  $children = element_children($element);

  if (count($children) > 0) {
    foreach ($children as $child) {
      $output .= render($element[$child]);
    }
  }

  $output .= '</' . $element['#tag'] . ">\n";
  $output .= '<div class="addthis_toolbox addthis_default_style addthis_32x32_style other">';
  $output .= '<a href="http://www.addthis.com/bookmark.php?v=300" class="addthis_button_email at300b" target="_blank" title="Email"></a>';
  $output .= '<a class="print" href="javascript:window.print()"><span class="sr-only">Print</span></a>';
  $output .= '<a href="http://www.addthis.com/bookmark.php?v=300" class="addthis_button_link at300b" target="_blank" title="Copy Link"></a>';
  $output .= '</div></div>';
  return $output;
}
