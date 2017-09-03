<?php

/**
 * Implements hook_preprocess_page().
 */
function si_baseline_preprocess_edan_search_results(&$vars) {
 // $query = drupal_get_destination();

    //$search_name = isset($vars['extra']['other_name'])? $vars['search_name']['other_name'] : $vars['search_name']['search_name'];
  if (in_array('location', $vars['search_name'])){
    libraries_load('masonry');
    $rendered_image = array();
    $classes = array('grid-item', 'col-sm-6', 'col-sm-4', 'col-md-3', 'col-wd-2', 'shadow');

    foreach ($vars['docs'] as $key => $doc) {
      $rendered_image = $url = '';
      if(!empty($doc['#title_link'])) {
        $query['width'] = '85%';
        $query['height'] = '85%';
        $query['iframe'] = 'true';
        $query = array_merge($query, $doc['#title_link']['query']);
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
            'uri' => $img_src . '358',
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
                'uri' => $img_src . '215',
                'width' => '238w'
              ),
              array(
                'uri' => $img_src . '380',
                'width' => '380w'
              ),
              array(
                'uri' => $img_src .'500',
                'width' => '500w'
              ),
            ),
            'sizes' => '(min-width: 500px) 50vw, (min-width: 682px) 33.3vw, (min-width: 980px)  25vw, (min-width: 1280px) 16.6vw, 100vw',
          );
          $rendered_image = theme('image_srcset', $image_info);

        }
        elseif (!empty($image['content'])) {
          $image_info = array(
            'src' => $image['content'],
            'attributes' => array()
          );
          $rendered_image = theme('image', $image_info);
        }
        $vars['docs'][$key]['#title_link']['rendered_path'] = isset($url) ? $url : (isset($image['extended']['full_size']) ? $image['extended']['full_size'] : $image['content']);
        // dpm($image_info);
      }
//      if(isset($doc['#title_link'])) {
//        $link_query = array_merge($query, $doc['#title_link']['query']);
//        $url = url($doc['#title_link']['path'], array('fragment' =>$doc['#title_link']['fragment'], 'query' => $link_query));
//      }
//      elseif($doc['#record_link']) {
//        $url = $doc['#record_link'];
//      }

      $vars['docs'][$key]['local_path'] = $url;
      $vars['docs'][$key]['row_attributes']['class'] = $classes;
      $vars['docs'][$key]['rendered_image'] = $rendered_image;
    }
    $vars['colorbox'] = TRUE;
    $vars['results_class'] = 'reset-list masonry-grid hover-title search-results';
    $vars['theme_hook_suggestions'][] = 'edan_search_results__mason';

  }

 // dpm($vars);
  if(isset($_GET['dpm-edan'])) {
    dpm($vars);
  }
}
