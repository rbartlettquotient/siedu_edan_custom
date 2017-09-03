
<?php

/**
 * Preprocess the primary theme implementation for a view.
 */
function si_baseline_preprocess_views_view(&$vars){
  global $base_path;
  $view = $vars['view'];
  //dpm($view);
//  dpm($view->display['panel_showtimes_movie']);
  $json_url = array(
    'showtimes' => 'showtimes/json/',
    'theaters' => 'showtimes/json/theater/'
  );
  if (strstr($view->current_display, 'panel_picker')) {
    $params = drupal_get_query_parameters();
    $date = '';
    $arg = current($view->args);
    $vars['json_url'] = url($json_url[$view->name] . $arg, array('absolute' => TRUE));
    // add datepicker
   // dpm($vars['view']->filter);
   // dpm($arg);
    drupal_add_library('system', 'ui.datepicker');
    if (isset($vars['view']->filter['field_date_value'])) {
      $date = strtotime($view->filter['field_date_value']->value['value']);
    }
    if (isset($vars['view']->filter['field_start_date_value'])) {
    //  dpm($vars['view']->filter['field_start_date_value']);
      $date = strtotime($view->filter['field_start_date_value']->value['value']);
    }

    $formatted_date = date('F j, Y', $date);
    $vars['title'] = t('Showtimes for') .' <span class="date">'. t('@date', array('@date' => $formatted_date)) .'</span>';

    $settings['view-'. $vars['dom_id']] = array(
      'picker_type' => $view->current_display === 'panel_picker__theater' ? 'theater' : 'default',
      'url' => url(current_path(), array('absolute' => TRUE)),
      'filterDate' => date('Y-n-j', $date)
    );
    drupal_add_js(array('siDatepicker' => $settings), 'setting');
    drupal_add_js(drupal_get_path('theme', 'si_baseline') .'/js/imax.js');
    $vars['theme_hook_suggestions'][] = 'views_view__panel_picker';

  }
  if (strstr($view->current_display,'panel_carousel_multiple')) {
    $loop = count($view->result) > 5 ? 'true' : 'false';
    $vars['theme_hook_suggestions'][] = 'views_view__panel_carousel';
    $vars['carousel_class'] = 'multiple';
    $settings = array(
      'owl' => array(
        'view-'. $vars['dom_id'] => array(
          //'center'=> 'true',
          'items' => 1,
          'loop' => 'true',
          'margin' => 10,
          'dots' => FALSE,
          'slideBy' => 1,
          'nav' => TRUE,
          'video' => TRUE,
          'pullDrag' => FALSE,
          //'freeDrag' => TRUE,
          'lazyLoad' => TRUE,
          'responsive' => array(
            '620' => array(
              'items' => 2,
              'slideBy' => 2,
              'stagePadding' => 20,
            ),
            '720' => array(
              'items' => 3,
              'slideBy' => 3,
              'stagePadding' => 50,

            ),
            '980' => array(
              'items' => 4,
              'slideBy' => 4,
              'stagePadding' => 50,
            )
//            '1920' => array(
//              'items' => 8,
//              'slideBy' => 7,
//            )
          )
        )
      )
    );
    if (isset($view->argument['field_theater_id_tid']) && isset($view->argument['field_theater_id_tid']->argument)) {
      $term = taxonomy_term_load($view->argument['field_theater_id_tid']->argument);
      $term_view = taxonomy_term_view($term, 'teaser');
      $header = render($term_view);
      $vars['header'] = $header;
    }
    if (isset($view->argument['field_imax_category_tid']) && isset($view->argument['field_imax_category_tid']->argument)) {
      $term = taxonomy_term_load($view->argument['field_imax_category_tid']->argument);
      $header = '<h2>'. l(t('@title', array('@title' => $term->name)), 'taxonomy/term/'. $term->tid) .'</h2>';
      $vars['header'] = $header;
    }
    drupal_add_js(drupal_get_path('theme', 'si_baseline').'/js/owl.carousel.min.js');
    drupal_add_js(drupal_get_path('theme', 'si_baseline') .'/js/slideshow.js', array('scope' => 'footer', 'weight' => 15));

    drupal_add_js(array('siSlides' => $settings), 'setting');
    // dpm($view->argument);
  }

  if($view->current_display == 'panel_carousel_multiple') {
    $filters = array();
   // dpm($view);

    foreach ($view->result as $id => $row) {
    // dpm($row->field_field_imax_category);
      if(isset($row->field_field_imax_category) && !empty($row->field_field_imax_category)) {
        foreach($row->field_field_imax_category as $category) {
          $filters[$category['raw']['tid']] = array(
            'title' => t('@title', array('@title' => $category['rendered']['#markup'])),
            'category' => drupal_html_class($category['rendered']['#markup']),
            'url' => url('movies/filter/'. current($view->args) .'/'. $category['raw']['tid'], array('absolute' => TRUE))
          );
        }

      }
    }
    $vars['si_filters'] = '';
    if(count($filters) > 1) {
      $items = array();
      foreach ($filters as $filter) {
        $items[$filter['title']] = $filter;
      }
      sort($items);
      $append = array(
        'title' => t('All'),
        'category' => 'category-all',
        'url' => url('movies/filter/'. current($view->args), array('absolute' => TRUE))
      );
      $vars['si_filters'] =  array_merge(array($append), $items);
    }
  }
  if($view->name == 'showtimes' || $view->name == 'theaters') {
   // libraries_load('bootstrap');
  }
  if (strstr($view->current_display,'panel_carousel_single')) {
  //  dpm($vars);
    $vars['theme_hook_suggestions'][] = 'views_view__panel_carousel';
    $settings = array(
      'owl' => array(
        'view-'. $vars['dom_id'] => array(
          'items' => 1,
          'loop' => 'true',
          'dots' => TRUE,
          'nav' => FALSE,
          'video' => TRUE,
          'lazyLoad' => TRUE,
          'autoplay' => TRUE,
          'autoplayHoverPause' => TRUE,
          'animateOut' => 'fadeOut',
          'autoplayTimeout' => 6000
        )
      )
    );
    $vars['carousel_class'] = 'single';
    drupal_add_js(drupal_get_path('theme', 'si_baseline').'/js/owl.carousel.min.js');
    drupal_add_js(drupal_get_path('theme', 'si_baseline') .'/js/slideshow.js', array('scope' => 'footer', 'weight' => 15));

    drupal_add_js(array('siSlides' => $settings), 'setting');
  }

}