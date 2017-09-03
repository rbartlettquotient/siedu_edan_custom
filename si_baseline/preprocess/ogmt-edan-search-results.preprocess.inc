<?php

/**
 * Implements hook_preprocess_page().
 */
function si_baseline_preprocess_ogmt_edan_search_results(&$vars) {
  libraries_load('masonry');
 // drupal_add_js(drupal_get_path('theme', 'si_baseline') .'/js/si_search.js', array('scope' => 'footer', 'weight' => 15));

 // $dest = drupal_get_destination();
//  if(isset($vars['pager'])) {
//    drupal_add_js(drupal_get_path('theme', 'si_baseline') .'/js/jquery.infinitescroll.js');
//  }
//  $searches = array(
//    'ogmt',
//    'smithsonian-highlights',
//    'art-and-design',
//    'history-and-culture',
//    'science-and-technology'
//  );
  $params = drupal_get_query_parameters();
 // dpm($params);
  $ogmt = in_array('ogmt', $vars['search_name']) ? TRUE : FALSE;
//  $masonry = array_intersect($vars['search_name'], $searches);
//  $masonry = empty($masonry) ? FALSE : TRUE;
 // $query = drupal_get_destination();
    $vars['colorbox'] = isset($params['iframe']) ? FALSE : TRUE;
    $rendered_image = array();
    $classes = array('grid-item', 'col-sm-6', 'col-sm-4', 'col-md-3', 'col-wd-2');
    foreach ($vars['docs'] as $key => $doc) {
      $vars['docs'][$key]['preface'] = $ogmt && isset($doc['content']['descriptiveNonRepeating']['data_source']) ? $doc['content']['descriptiveNonRepeating']['data_source'] : '';

      $rendered_image = $url = '';
      if(!empty($doc['#title_link'])) {
        $query['width'] = '85%';
        $query['height'] = '85%';
        $query['iframe'] = 'true';

       // $query['scrolling'] = 'false';
        if(!$vars['colorbox']) {
          $query['back_link'] = TRUE;
        }
        $query['destination'] = current_path();

        $query = array_merge($query, $doc['#title_link']['query']);
       // dpm($query);
        $url= url($doc['#title_link']['path'], array('fragment' =>$doc['#title_link']['fragment'], 'query' => $query));
        $vars['docs'][$key]['#title_link']['rendered_path'] = $url;
      }
      else {
        $vars['docs'][$key]['#title_link']['rendered_path'] = '#';
      }
      if (!empty($doc['siedu_media'])) {
        $image = current($doc['siedu_media']);
        $classes[] = 'has-media';
        if (!empty($image['extended']['idsData']) && module_exists('picture')) {
          $img_src = $image['extended']['idsData']['idsURL'] . '?id=' . $image['extended']['idsData']['idsID'] . '&max_w=';
          $image_info = array(
            'uri' => $img_src . '360',
            'path' => NULL,
            'width' => NULL,
            'height' => NULL,
            'alt' => '',
            'title' => NULL,
            'attributes' => array(),
            'srcset' => array(
              array(
                'uri' => $img_src . '238',
                'width' => '238w'
              ),
              array(
                'uri' => $img_src . '200',
                'width' => '200w'
              ),
              array(
                'uri' => $img_src . '300',
                'width' => '300w'
              ),
              array(
                'uri' => $img_src . '350',
                'width' => '350w'
              ),
            ),
            'sizes' => '(min-width: 500px) 50vw, (min-width: 682px) 33.3vw, (min-width: 980px)  25vw, (min-width: 1280px) 16.6vw, 100vw',
          );

          $rendered_image = theme('image_srcset', $image_info);
        }
        elseif (!empty($image['content'])) {
          $image_info = array(
            'src' => $image['content'],
            'alt' => ''
          );
          $rendered_image = '<img' . drupal_attributes($image_info) . ' />';
        }
        $vars['docs'][$key]['#title_link']['rendered_path'] = isset($url) ? $url : (isset($image['extended']['full_size']) ? $image['extended']['full_size'] : $image['content']);

        // dpm($image_info);
      }
//      if(isset($doc['#title_link'])) {
//        $link_query = array_merge($query, $doc['#title_link']['query']);
//        $url = url($doc['#title_link']['path'], array('fragment' =>$doc['#title_link']['fragment'], 'query' => $link_query));
//      }
      $vars['docs'][$key]['local_path'] = $url;
      $vars['docs'][$key]['rendered_image'] = $rendered_image;
     // if ($masonry) {
        $vars['docs'][$key]['row_attributes']['class'] = $classes;
      //}
    }
 // if ($masonry) {
    libraries_load('imagesloaded');
    libraries_load('masonry');
    $vars['results_class'] = 'reset-list masonry-grid search-results';
    $vars['results_class'] .= $ogmt ? '' : ' hover-title';
    $vars['theme_hook_suggestions'][] = 'edan_search_results__mason';
 // }
  if(isset($_GET['dpm-edan-ogmt'])) {
    dpm($vars);
  }
}
