<?php

/**
 * Implements hook_preprocess_page().
 */
function si_baseline_preprocess_edan_custom_search_results(&$vars) {
  $start = microtime(TRUE);
  $dest = drupal_get_destination();
  $settings = array();
  $list = array(
    'cultural-centers',
    'research-centers0'
  );
  $museums = array(
    'about-us-museums-a',
    'museum'
  );

  $exhibits = array(
    'Current' => 'exhibits-current',
    'Closing Soon' => 'exhibits-closing',
    'Upcoming'=> 'exhibits-upcoming',
    'Past' => 'exhibits-past',
    'Online' => 'exhibits-online',
  );
  $slideshow = array(
    'whats-on-closing',
    'whats-on-recent',
    'what-s-on-kids-fav',
    'whats-on-featured',
    'exhibitions-wwi100',
    'exhibitions-asia'
  );

  $sisearches = array(
    'collection-images',
    'video',
    'search-exhibitions',
    'articles',
    'search-all-else',
  );
  $vars['id'] = $vars['search_name'];

  $search_name = $vars['search_name'];
//  $feature = $vars['search_name'] === 'exhibits-current' && (!isset($dq['page']) || $dq['page'] < 1);
  $feature = $search_name === 'exhibits-current';


  if($vars['search_form']) {
    if(!in_array($search_name, $sisearches)) {
      $dq = drupal_get_query_parameters();
      $form = drupal_get_form('siedu_searches_facets_form', $vars['edan_facets'], $vars['search_name'], $dq, TRUE);
      $vars['facets'] = render($form);

    }
    else {
      $dq = drupal_get_query_parameters();
      $form = drupal_get_form('siedu_searches_facets_form', $vars['edan_facets'], $vars['search_name'], $dq);
      $vars['facets'] = render($form);

    }
  }

  $vars['container_class'] =  in_array($vars['search_name'], $exhibits) ? 'grid-wrapper search-results-container': 'search-results-container';
  $vars['container_class'] .= $feature ? ' feature' : '';

  $vars['results_class'] = 'reset-list search-results';

  if (in_array($search_name, $list)) {
    $vars['theme_hook_suggestions'][] = 'edan_custom_search_results__list_view';
  }
  if (in_array($search_name, $exhibits, TRUE)) {
    $params = drupal_get_query_parameters();
    $buttons = $vars['page_title'] = '';
    if ($vars['search_form']) {
      $custom_searches = variable_get('edan_custom_searches');
      $current_search = $custom_searches[$search_name];
      $vars['page_title'] = $current_search['menu_results_title'];
      foreach ($exhibits as $title => $search) {
        $search_detail = $custom_searches[$search];
        $classes = array(
          'btn',
          'btn-large',
          'btn-alt'
        );
        $classes[] = $search_name === $search ? 'active' : '';

        $buttons[] = l(t($title), $search_detail['menu_results_page'], array('attributes' => array('class' => $classes), 'query' => $params));
//      $vars['event_status'] = strtolower($content['event_status']['content']) == 'onview ';

      }

    }
    $vars['buttons'] = $buttons;
    $vars['theme_hook_suggestions'][] = 'edan_custom_search_results__exhibits';

    $vars['destination'] = $dest['destination'];
    $vars['id'] = drupal_html_id($vars['search_name']);
    si_baseline_process_exhibits($vars, 'max_h', $feature);
  }
  elseif (in_array($vars['search_name'], $slideshow)) {
    $vars['id'] =  drupal_html_id($vars['search_name']);
    $settings['slider'] = array(
      $vars['id'] => $vars['id']);
    $vars['destination'] = $dest['destination'];
    si_baseline_process_exhibits($vars, 'max_h');
    drupal_add_js(array('siSlides' => $settings), 'setting');

    drupal_add_js(drupal_get_path('theme', 'si_baseline') .'/js/swiper.jquery.min.js', array('scope' => 'footer'));
    drupal_add_js(drupal_get_path('theme', 'si_baseline') .'/js/slideshow.js', array('scope' => 'footer', 'weight' => 15));

    $vars['theme_hook_suggestions'][] = 'edan_custom_search_results__exhibit_slideshow';

  }
  elseif (in_array($search_name, $museums) || in_array($search_name, $museums)) {
    foreach($vars['docs'] as $key => $doc) {
      $url = '';
      if (isset($doc['siedu_media'])) {
        $image = current($doc['siedu_media']);
//        if(!empty($image['extended']['idsData'])) {
////          $image_url = url($image['extended']['idsData']['idsURL'], $image['extended']['idsData']['options']);
////          $image_url .= empty($image['extended']['idsData']['options']['query']) ? '?' : '&';
////          $image_url .= 'id='. $image['extended']['idsData']['idsID'] .'&max_h=300';
//          $vars['docs'][$key]['img_uri'] = $image['content  '];
//        }
        $vars['docs'][$key]['img_uri'] = $image['content'];
      }
      if(!empty($doc['#title_link'])) {
        $url = url($doc['#title_link']['path'], array('fragment' =>$doc['#title_link']['fragment'], 'query' => $doc['#title_link']['query']));
      }
      $vars['docs'][$key]['local_path'] = $url;
    }

    $vars['theme_hook_suggestions'][] = 'edan_custom_search_results__museums_grid_view';
  } // end museum search results

  elseif(in_array($search_name, $sisearches)) {
    $container_classes = array(
      'collection-images' => 'masonry-grid-wrapper search-results-container',
      'video' => 'grid-wrapper equal-col search-results-container',
      'search-exhibitions' => 'masonry-grid-wrapper search-results-container',
      'articles' => 'search-results-container',
      'search-all-else' => 'search-results-container'
    );

    $results_classes = array(
      'collection-images' => 'masonry-grid reset-list',
      'video' => 'reset-list content',
      'search-exhibitions' => 'reset-list masonry-grid',
      'articles' => 'reset-list search-list split-list',
      'search-all-else' => 'reset-list search-list'
    );
    $row_classes = array(
      'collection-images' => array('grid-item', 'col-sm-6','col-md-4', 'col-wd-2', 'shadow'),
      'search-exhibitions' => array('grid-item', 'col-sm-6','col-md-4', 'col-wd-2'),
      'video' => array('col', 'col-sm-6','col-md-4','col-wd-3'),
      'articles' => array('search-result'),
    );
    $resp_images = array(
      'collection-images',
      'search-exhibitions',
      'video'
    );
    $vars['results_class'] = $results_classes[$search_name];
    $vars['results_class'] .= ' search-results';
    $vars['container_class'] = $container_classes[$search_name];
    $vars['container_class'] .= ' block block--'. $search_name;
    foreach ($vars['docs'] as $key => $doc) {
      $rendered_image = $url = '';
      $result_class = in_array($search_name, $resp_images) ? array('node--teaser', 'node--teaser-long') : array('node--teaser', 'node--teaser-featured') ;
      if(!empty($doc['#title_link'])) {
        $query['width'] = '85%';
        $query['height'] = '85%';
        $query['iframe'] = 'true';
        $query['destination'] = $dest['destination'];
        $query = array_merge($query, $doc['#title_link']['query']);
        $url= url($doc['#title_link']['path'], array('fragment' =>$doc['#title_link']['fragment'], 'query' => $query));
        $vars['docs'][$key]['#title_link']['rendered_path'] = $url;
      }
//      else {
//        $vars['docs'][$key]['#title_link']['rendered_path'] = '#';
//      }

      $vars['docs'][$key]['local_path'] = $url;

      if (!empty($doc['siedu_media'])) {
        $image = current($doc['siedu_media']);
        $result_class[] = 'has-media';
        if (!empty($image['extended']['idsData']) && module_exists('picture')) {
          $img_src = $image['extended']['idsData']['idsURL'] . '?id=' . $image['extended']['idsData']['idsID'] . '&max_w=';
          if (in_array($search_name, $resp_images)) {
            $image_info = array(
              'uri' => $img_src . '300',
              'path' => NULL,
              'width' => NULL,
              'height' => NULL,
              'alt' => '',
              'title' => NULL,
              'attributes' => array(),
              'srcset' => array(
                array(
                  'uri' => $img_src . '230',
                  'width' => '230w'
                ),
                array(
                  'uri' => $img_src . '450',
                  'width' => '400w'
                ),
              ),
              'sizes' => '(min-width: 500px) 50%, (min-width: 980px)  33%, (min-width: 1280px) 25%, 100%',
            );
            $rendered_image = theme('image_srcset', $image_info);
          }

          else {
            $image_info = array(
              'src' => $img_src .'150',
              'alt' => ''
            );
            $rendered_image = '<img' . drupal_attributes($image_info) . ' />';
          }
        }
        elseif (!empty($image['content'])) {
          $image_info = array(
            'src' => $image['content'],
            'alt' => ''
          );

          $rendered_image = '<img' . drupal_attributes($image_info) . ' />';
        }
        $vars['docs'][$key]['#title_link']['rendered_path'] = !empty($url) ? $url : (isset($image['extended']['full_size']) ? $image['extended']['full_size'] : $image['content']);
      }
     if(isset($row_classes[$search_name])) {
       $vars['docs'][$key]['row_attributes']['class'] = $row_classes[$search_name];
     }
      $vars['docs'][$key]['row_attributes']['class'][] =  $key % 2 ? 'odd' : 'even';
      //$vars['docs'][$key]['url'] = $url;

      switch ($search_name) {
        case 'video':
          $video = current($doc['grouped_media']['video']);
          $vars['docs'][$key]['description'] = '';

          $image_info = array(
            'src' => empty($video['extended']['thumbnail']) ? '/'. drupal_get_path('theme', 'si_baseline') .'/images/media-placeholder.png' : $video['extended']['thumbnail'],
            'alt' => ' '
          );
          $rendered_image = '<img' . drupal_attributes($image_info) . ' />';
          $result_class[] = empty($video['extended']['thumbnail']) ? 'placeholder-image' : 'image';
          break;
        case 'collection-images':
          $vars['docs'][$key]['description'] = '';
          $vars['docs'][$key]['preface'] = isset($doc['content']['descriptiveNonRepeating']['data_source']) ? $doc['content']['descriptiveNonRepeating']['data_source'] : '';

        break;
        case 'search-exhibitions':
         // $url = !empty($doc['content']['online_exhibit']) ? $doc['content']['online_exhibit'] : $url;

          $vars['docs'][$key]['#title_link']['rendered_path'] = $url;

          $vars['docs'][$key]['description'] =  $doc['#formatted_location'] ? $doc['#formatted_location'] .'<br />' : '';
          $vars['docs'][$key]['description'] .= $doc['#full_date'];
         // $vars['docs'][$key]['description'] .= !empty($doc['teaser']) ? '<p>'. text_summary($doc['teaser'], NULL, 300) .'</p>' : '';
          $path =  !empty($doc['content']['online_exhibit']) ? $doc['content']['online_exhibit'] : $url;
          $vars['docs'][$key]['description'] .= !empty($doc['content']['online_exhibit']) ?
            '<p>'. l(t('View Online Exhibit'), $path, array('attributes' => array('class' => array('btn-text'), 'target'=> '_blank'))) .'</p>': '';

      break;
        case 'search-all-else':
        case 'articles':
        //$url .= $search_name === 'articles' ? '&searchpage=true' : '';
        $vars['docs'][$key]['description'] = isset($doc['content']['descriptiveNonRepeating']['data_source']) ? '<p class="preface">'. $doc['content']['descriptiveNonRepeating']['data_source'] .'</p>': '';
        $description = '';
        if (isset($doc['teaser']) && strlen($doc['teaser']) > 0) {
          $description = check_markup($doc['teaser'], 'edan_text');
        }
        elseif (isset($doc['description']) && strlen($doc['description']) > 0) {
          $description = check_markup($doc['description'], 'edan_text');
          $description = text_summary($description, NULL, 200);
        }

        $vars['docs'][$key]['description'] .= $description;
        $vars['docs'][$key]['description'] .= isset($url) ? '<p><a href="'. $url .'" class="btn-text colorbox-load">'.t('Learn More') .'</a></p>' : '';
          break;
      }
      $vars['docs'][$key]['result_class'] = implode(' ', $result_class);
      $vars['docs'][$key]['rendered_image'] = $rendered_image;
      $vars['docs'][$key]['#title'] = isset($url) ? '<a href="'. $url .'" class="colorbox-load">'. t($vars['docs'][$key]['title']) .'</a>': $vars['docs'][$key]['#title_plain'];

    }

    $vars['theme_hook_suggestions'][] = 'edan_custom_search_results__default';
  } // end sisearch results
  else {
    foreach($vars['docs'] as $key => $doc) {
      $description = '';
      if (isset($doc['teaser']) && strlen($doc['teaser']) > 0) {
        $description = check_markup($doc['teaser'], 'edan_text');
      }
      elseif (isset($doc['description']) && strlen($doc['description']) > 0) {
        $description = check_markup($doc['description'], 'edan_text');
        $description = text_summary($description, NULL, 200);
      }
      $vars['docs'][$key]['teaser'] = $description;

    }
  }

  if($search_name == 'collection-images' || $search_name == 'search-exhibitions') {
    libraries_load('masonry');
  }

  if(isset($_GET['dpm-edan'])) {
    dpm($vars);
  }
  if (defined('EDAN_TEST') && EDAN_TEST) {

    $GLOBALS['EDAN_TEST']['edan_custom_search_theme_preprocess'][] = microtime(TRUE) - $start;
  }

}


function si_baseline_process_exhibits(&$vars, $constrain = 'max', $feature = FALSE) {
  foreach($vars['docs'] as $i => $doc) {
    $rendered_image = '';
    $vars['docs'][$i]['row_attributes']['id'] = 'fjs_'. $i;
    $class = $doc['row_attributes']['class'];
    $class[] = 'col';
//    $class[] = 'no-spacing';

    if (!empty($doc['siedu_media']) && is_array($doc['siedu_media'])) {
      $image = current($doc['siedu_media']);
      $class[] = 'has-media';
//      if (!empty($image['extended']['idsData']) && module_exists('picture')) {
//        $img_src = $image['extended']['idsData']['idsURL'] . '?id=' . $image['extended']['idsData']['idsID'] . '&'.$constrain .'=';
//        if ($i < 4 && $feature) {
//          $image_info = array(
//            'uri' => $img_src . '380',
//            'path' => NULL,
//            'width' => NULL,
//            'height' => NULL,
//            'alt' => '',
//            'title' => NULL,
//            'attributes' => array(),
//            'srcset' => array(
//              array(
//                'uri' => $img_src .'=380',
//                'width' => '335w'
//              ),
//              array(
//                'uri' => $img_src .'=450',
//                'width' => '450w'
//              ),
//              array(
//                'uri' => $img_src .'=535',
//                'width' => '535w'
//              )
//            ),
//            'sizes' => '(min-width: 500px) 50%, (min-width: 980px)  33%, 100%',
//          );
//          $rendered_image = theme('image_srcset', $image_info);
//        }
//        else {
////          $image_info = array(
////            'uri' => $img_src . '300',
////            'path' => NULL,
////            'width' => NULL,
////            'height' => NULL,
////            'alt' => '',
////            'title' => NULL,
////            'attributes' => array(),
////            'srcset' => array(
////              array(
////                'uri' => $img_src . '335',
////                'width' => '200w'
////              ),
////              array(
////                'uri' => $img_src . '400',
////                'width' => '400w'
////              ),
////            ),
////            'sizes' => '(min-width: 500px) 50%, (min-width: 768px) 33%, (min-width: 980px)  25%, (min-width: 1280px) 16%, 100%',
////          );
//          $image_info = array(
//            'src' => $img_src .'330',
//            'alt' => ''
//          );
//
//          $rendered_image = '<img' . drupal_attributes($image_info) . ' />';
//        }
//
//      }
      if (!empty($image['content'])) {
        $image_info = array(
          'src' => $image['content'],
          'alt' => '',
          'class' => 'exhibit-image'
        );

        $rendered_image = '<img' . drupal_attributes($image_info) . ' />';
      }
      $vars['docs'][$i]['rendered_image'] = $rendered_image;
    }
    else {
      $class[] = 'no-media';
    }
    $vars['docs'][$i]['row_attributes']['class'] = $class;
  }

}