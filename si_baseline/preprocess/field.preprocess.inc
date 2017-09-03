<?php

/**
 * @file
 * Contains a pre-process hook for 'html'.
 */

/**
 * Implements hook_preprocess_html().
 */
function si_baseline_preprocess_field(&$vars) {

  $element = $vars['element'];
  $entity = $element['#object'];
  //dpm($vars);

  if ($element['#field_name'] === 'field_section_title' && $element['#bundle'] == 'tableau_card') {
    foreach ($vars['items'] as $delta => $value) {
      $content = '<h2>';
      $content .= '<a name="'.  drupal_html_id(trim($value['#markup'])) .'">'. $value['#markup'] .'</a>';
      $content .= '</h2>';
      $vars['items'][$delta]['#markup'] = $content;
    }
  }
  if ($element['#field_name'] == 'field_theater_id' || $element['#field_name'] == 'field_start_date' || $element['#field_name'] == 'field_on_sale_date') {
    $vars['theme_hook_suggestions'][] = 'field__field_ticket_group';
  }
  if ($element['#field_name'] == 'field_url' && $element['#bundle'] == 'ticket_info') {
    $text = t('Buy Tickets');
    $text .= '<span class="sr-only"> '. t('for @title at ', array('@title' => $element['#movie']));
    $text .= isset($element['#theater']) ? $element['#theater'] : '';
    $text .= '</span>';

    foreach ($vars['items'] as $delta => $item) {
      $vars['items'][$delta]['#element']['attributes']['data-message'] ='';
      $vars['items'][$delta]['#element']['title'] = $text;
      $vars['items'][$delta]['#element']['html'] = TRUE;
    }
  }
}
