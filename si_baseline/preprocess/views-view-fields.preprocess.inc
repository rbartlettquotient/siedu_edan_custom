<?php

/**
 * Preprocess the views fields to add showtimes on the theater page
 */
function si_baseline_preprocess_views_view_fields(&$vars) {
  $view = $vars['view'];
  $now = strtotime('now');
  $row = $vars['row'];

  if ($view->name == 'theaters') {
    $append = array(
      'panel_carousel_multiple' => 'item_id',
      'panel_picker__theater' => 'body',
      'page_filter' => 'item_id',
      'panel_pane_category' => 'body',
    );

//    dpm($row->field_field_start_date);
  //  dpm($vars['row']);
    $start = isset($row->field_field_start_date) && !empty($row->field_field_start_date) ? strtotime($row->field_field_start_date[0]['raw']['value'] . ' ' . $row->field_field_start_date[0]['raw']['timezone']) : $now;

    $date =isset($vars['view']->filter['field_start_date_value'])? $view->filter['field_start_date_value']->value['value'] : ($view->current_display === 'panel_pane_category' ? date('Y-n-j', $start) : NULL);
    //dpm($date);
    $show_time =  $view->current_display == 'panel_picker__theater' ? TRUE: ($now > $start ? TRUE : FALSE);
   // dpm($view->current_display != 'page_filter');
    foreach ($vars['fields'] as $field_name => $field) {
      if (isset($append[$view->current_display]) && $field_name == $append[$view->current_display] && isset($row->paragraphs_item_field_data_field_ticket_info_item_id)) {

        $id = $row->paragraphs_item_field_data_field_ticket_info_item_id;
        if (in_array($view->current_display, array('panel_picker__theater', 'panel_pane_category'))) {
          $class = 'movie-info views-field-' . $field->class;
          $field->wrapper_prefix = '<div class="' . $class . '">';
        }
        $content = $field_name == 'item_id' ? '' : $field->content;
     //   $result = views_get_view_result('showtimes', 'panel_showtimes_movie', $id, $date);
        $content .= views_embed_view('showtimes', 'panel_showtimes_movie', $id, $date);
        $field->content = $content;
      }

//      if ((strstr($view->current_display,'panel_carousel') === FALSE &&  $view->current_display != 'page_filter') && $field_name != 'field_image') {
//        $class = 'movie-info views-field-' . $field->class;
//        $field->wrapper_prefix = '<div class="' . $class . '">';
//      }
      $vars['fields'][$field_name] = $field;
    }
   // dpm($vars['fields']);
    if($view->current_display == 'panel_coming_soon') {
      $field = $vars['fields']['rendered_entity'];
      $class = 'movie-info views-field-' . $field->class;
      $vars['fields']['rendered_entity']->wrapper_prefix = '<div class="' . $class . '">';
     // dpm($vars['fields']);
    }
    if ($now > $start) {
      unset($vars['fields']['rendered_entity']);
    }
    else {
      unset($vars['fields']['item_id']);
    }

  }
  if($view->name == 'dashboard_menu') {
    foreach ($view->field as $id => $field) {
      if (isset($vars['fields'][$id])) {
        $vars['fields'][$id]->wrapper_prefix = '';
        $vars['fields'][$id]->content = $view->style_plugin->get_field($view->row_index, $id);
        $vars['fields'][$id]->wrapper_suffix = '';
      }
    }

  }


//  if ($view->name == 'movies_json') {
//    $args = $view->args;
//   // dpm($vars['fields']);
//    $id = $row->paragraphs_item_field_data_field_ticket_info_item_id;
//    $date =isset($args[1])? $args[1] : NULL;
//    $field = $vars['fields']['nothing'];
//    $field->content = views_embed_view('showtimes', 'panel_showtimes_movie', $id, $date);
//    $vars['fields']['nothing'] = $field;
//  }
}
