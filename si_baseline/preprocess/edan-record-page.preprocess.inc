<?php

/**
 * Implements hook_preprocess_page().
 */
function si_baseline_preprocess_edan_record_page(&$vars) {

  $params = drupal_get_query_parameters();
  $vars['show_backLink'] = isset($params['back_link']);
 // $start = microtime(TRUE);

  $dest = isset($params['destination']) ? $params['destination'] : '';
  $vars['back_link'] = '';
  $site_app_id = variable_get('edan_app_id');
	if (!empty($dest)) {
		$url = drupal_parse_url($dest);
		//dpm($url);
    if (isset($params['back_link'])) {
      $url['query']['iframe'] = 'true';
    }
    $link_text = '<span class="fa fa-angle-double-left" aria-hidden="true"></span>' .t('Previous Page');

    $vars['back_link'] = l($link_text, $url['path'], array(
															'query' => $url['query'], 
															'fragment' => $url['fragment'], 
															'html' => TRUE,
															));
	}

  $vars['is_external'] = FALSE;
  $image_settings = variable_get('siedu_edan_image', array());
  $thumbsize = isset($image_settings['thumbnail']) ? $image_settings['thumbnail'] : 'max=200';
	$docs = $vars['docs'];

	foreach ($docs as $i => $doc) {
    if($doc['type'] !== 'edanead') {
      $unit_start = microtime(TRUE);
      if ($i == 0 && isset($doc['content']['descriptiveNonRepeating']['unit_code']) && strlen($doc['content']['descriptiveNonRepeating']['unit_code']) > 0) {
        $unitAppId = '';
        $unit_info = _get_applicationId_from_unitCode($doc['content']['descriptiveNonRepeating']['unit_code'], TRUE);
        if (is_array($unit_info)) {
          $unitAppId = $unit_info['app_id'];
          $unit = _edan_search_process_rows($unit_info['docs']);
        }
        $vars['is_external'] = $site_app_id !== $unitAppId;
        if ($vars['is_external'] && isset($unit[0])) {
          $unit = $unit[0];
          $vars['unit_info'] = $unit;
         // $unit_classes = array('unit-info', 'pane-node-field-tagline', 'flex-column');
          $unit_classes = array('unit-info', 'pane-node-field-tagline');

          if(!empty($unit['content']['unit_codes'])) {
            $unit_classes[] = 'has-unit-code';
            foreach ($unit['content']['unit_codes'] as $unit_code) {
              $unit_classes[] = drupal_html_class($unit_code);
            }
          }
          if (!empty($unit['#title_plain'])) {
            $unit_classes[] = drupal_html_class($vars['unit_info']['#title_plain']);
            $vars['unit_link'] = !empty($unit['#title_link']) ?
              l('<span>'. t($unit['#title_plain']) .'</span>', $unit['#title_link']['path'], array('attributes'=> array('class' => array('delta'), 'target'=> '_blank'), 'html' => TRUE)) : '';

          }
          $unit_classes = implode(' ', $unit_classes);
          $vars['unit_class'] = $unit_classes;
        }
        else {
          $vars['unit_link'] = '';
        }
      }
      $vars['unit_link'] = '';
      $unit_end = microtime(TRUE);
      if (defined('EDAN_TEST')) {$GLOBALS['EDAN_TEST']['unit_process'][] =  $unit_end - $unit_start; }
      $info_start = microtime(TRUE);
      $items = $attributes = $media  = $slideshow = array();
     // $attributes['class'][] = 'search-results';
      $attributes['class'][] = 'l-container';
      $attributes['class'][] = isset($doc['flags']['in_list']) && $doc['flags']['in_list'] === TRUE ? ' in-list' : '';
      $attributes['id'] = $doc['content']['descriptiveNonRepeating']['record_ID'];
      $vars['docs'][$i]['rendered_media'] = '';
      foreach ($doc['content']['freetext'] as $field => $vals) {
        foreach ($vals as $key => $value) {
          $items[$field][$key] = array(
            'label' => t($value['label']),
            'content' =>  t($value['content'])
          );
        }
      }
      $vars['docs'][$i]['content']['freetext'] = $items;
      $grouped = array();
      //media processing
      $doc['siedu_media'] = array();
      $record_data = array_key_exists('record_data', $doc) ? $doc['record_data'] : NULL;
      $record_title = array_key_exists('#title', $doc) ? $doc['#title'] : '';
      if(strlen($record_title) > 0 && isset($record_data)) {
        $record_images = siedu_edan_custom_get_media($record_data, $record_title);
        $doc['grouped_media'] = array_key_exists('grouped_media', $record_images) ? $record_images['grouped_media'] : array();
        $doc['siedu_media'] = array_key_exists('siedu_media', $record_images) ? $record_images['siedu_media'] : array();
      }

      if(!empty($doc['siedu_media'])) {
        $attributes['class'][] = 'has-media';
        $media =  $settings = $media_cnt = array();
        foreach ($doc['siedu_media'] as $key => $asset) {
          switch ($asset['extended']['type']) {
            case 'images':
              $asset['content'] = !empty($asset['extended']['idsData']) ? $asset['extended']['idsData']['idsDynamic'] .'&inline=true' : $asset['content'];
              $grouped['slideshow'][] = $asset;

              break;
            case 'slideshowxml':
              $caption = '';
              $xml = simplexml_load_file($asset['content']);
              //dpm($xml);
              foreach($xml as $item) {
                $caption = isset($item->caption) && !empty($item->caption) ? (string)$item->caption : $caption;
                $path = (string)$item->NAME;
                $ids = getIDS($path);
//                dpm($ids);
//                dpm($thumbsize);
                $thumbsize = is_array($thumbsize) ? '&'. implode('=', $thumbsize) : NULL;
                $thumb = !empty($ids) ? $ids['idsURL'] .'?id='. $ids['idsID'] . $thumbsize : $path;
                $link_path = !empty($ids) ? $ids['idsDynamic'] .'&inline=true' : $path;

                $grouped['slideshow'][] = array(
                  'content' => $link_path,
                  'extended' => array(
                    'caption' => $caption,
                    'idsData' => $ids,
                    'type' => 'images',
                    'thumbnail' => $thumb,
                    'alt_text' => 'images for '. $doc['#title_plain']
                  )
                );
              }
//              unset($media['slideshowXML']);
//              $media['slideshow'][] = $slides;
              break;
            case 'url':
              //foreach($assets as $asset) {
              $response = isUrlExists($asset['content']);
              if ($response['status']) {
                if (strstr($asset['content'], 'google.com/map')) {
                  preg_match('/-?([1-8]?[0-9]\.{1}\d{1,6}|90\.{1}0{1,6}),-?([1]?[1-7]?[0-9]\.{1}\d{1,6}|180\.{1}0{1,6})/', $asset['content'], $matches);
                  if (!empty($matches)) {
                    $location = current($matches);
                    $asset['content'] = 'https://www.google.com/maps/embed/v1/place?key=AIzaSyDe_paOqwgI1s5R1hyD-FmpjkMSD-zBlSQ&q=' . $location . '&zoom=13';

                  }
                  $grouped['slideshow'][] = $asset;
                }
                else {
                  $grouped['other'][] = $asset;
                }
              }

              //}
              break;
            case 'video':
            case 'audio':
            case 'pdf':
              $grouped['slideshow'][] = $asset;
              break;
            default:
//            $media_cnt[$type]++;
//            $id = $type .'-'. $i .'-'. $media_cnt[$type];
//            $media[$id] =  $asset;
              $grouped['other'][] = $asset;
              break;

          }


        }
      }
      elseif(isset($doc['content']['descriptiveNonRepeating']['record_link'])) {
        $grouped['other'][] = array(
          'content' => $doc['content']['descriptiveNonRepeating']['record_link'],
          'extended' => array(
            'record_title' => $doc['#title_plain']
          )
        );

      }
      if (defined('EDAN_TEST')) {$GLOBALS['EDAN_TEST']['si_edan_record_preprocess_group'][] = microtime(TRUE)-$info_start; }

      if(!empty($grouped)) {
        $media = array();
        foreach($grouped as $type => $values) {
          if($type == 'slideshow') {
            $media['slideshow'] = $values;
          }
          else {
            $media['other'] = $values;
          }
        }
      //  dpm($media);
        $vars['docs'][$i]['rendered_media'] = _media_theme($media, $i);
      }


      $attributes['class'] = array_filter($attributes['class']);
      $vars['docs'][$i]['row_attributes'] = $attributes;
    }

  }  // end foreach($docs)
// $end = microtime(TRUE);
//  if (defined('EDAN_TEST') && EDAN_TEST) {$GLOBALS['EDAN_TEST']['si_edan_record_preprocess'][] = $end-$start; }

//	dpm($vars);

}

function _media_theme($assets, $delta) {
  $start = microtime(TRUE);
  $items = $settings = array();
  $output = $output_slide = $output_other = '';
  $theme = drupal_get_path('theme', 'si_baseline');
  //construct slideshow
  if (isset($assets['slideshow'])) {
    $cnt = count($assets['slideshow']);
    //display media if only one
    if($cnt == 1){
      foreach ($assets['slideshow'] as $key => $media) {
        $output_slide .= '<div class="media-container active media-'. strtolower(drupal_clean_css_identifier($media['extended']['type'])) .'">';
        if($media['extended']['type'] === 'images') {
          $id = 'image-'. $delta .'-'. $key;
          $img_src = empty($media['extended']['idsData']) ? $media['content'] : $media['extended']['full_size'];

          $image_info = array(
            'src' => $img_src,
            'alt' => $media['extended']['alt_text'],
            'id' => $id
          );
          $output_slide .= '<img' . drupal_attributes($image_info) . ' />';
          if (!empty($media['extended']['idsData'])) {
            $settings['images'][$id] = array(
              'src' => array(
                'default' => $media['content'],
                'mobile' => isset($media['extended']['medium_size']) ? $media['extended']['medium_size'] : $media['content'],
                'fullscreen' => $media['extended']['idsData']['idsURL'] .'?id='. $media['extended']['idsData']['idsID']
              ),
              'type' => $media['extended']['type'],
              'info' => $media['extended']['alt_text'] ,
              'caption' => '',
            );
          }
        }
        elseif ($media['extended']['type'] === 'video') {
          if (isset($media['rendered'])) {
            $output_slide .='<div class="wrapper--video">'. $media['rendered'] .'</div>';
          }
          else {
            $id = 'video-'. $delta .'-'. $key;
            $item = array(
              'file' => $media['content'],
              'image' => isset($media['extended']['thumbnail'])  ? $media['extended']['thumbnail'] : $theme .'/images/media-placeholder.png'
            );
            $output_slide .= theme('si_jw_player', array('source' => $item, 'html_id' => $id, 'preset' => 'default'));

          }
        }
        elseif($media['extended']['type'] === 'audio') {
          $id = 'audio-'. $delta .'-'. $key;
          $item = array(
            'file' => $media['content'],
            'image' => $theme .'/images/media-placeholder.png'
          );
          $output_slide .= theme('si_jw_player', array('source' => $item, 'html_id' => $id, 'preset' => 'audio'));
        }
        else {
          $output_slide .= '<iframe title="'. $media['extended']['alt_text'] .'" src="'. $media['content'] .'" width="100%" height="500" frameborder="0" scroll="no"></iframe>';

          //settings to pass to javascript to build media container.
        }
        $output_slide .= '</div>';
      }
    } // end single media if statement
    else {
      $slides = $media_cnt = array();
      $slideID = uniqid('swiper-');
      $output_slide .= '<div class="media-container media-multiple">';
      $output_slide .= '</div>';

      foreach ($assets['slideshow'] as $key => $media) {
        $type =  $media['extended']['type'] === 'images' ? 'image' :  $media['extended']['type'];
        $id = $type .'-'. $delta .'-'. $key;
        $caption = isset($media['caption']) ? $media['caption'] :'';
        $media_cnt[$media['extended']['type']] = isset($media_cnt[$media['extended']['type']]) ? $media_cnt[$media['extended']['type']]: 1;

        $options = array(
          'attributes' => array(
            'id' => $id,
            'class' => array(
              $media['extended']['type'] === 'images' ? (empty($media['extended']['idsData']) ? 'image' : 'idsDynamic') : $media['extended']['type']
            )
          ),
          'html' => TRUE
        );

        if (!empty($media['extended']['thumbnail'])) {
          $thumbnail = '<img src="' . $media['extended']['thumbnail'] .'" alt="'. $media['extended']['alt_text'] .'-thumbnail ' .   $media_cnt[$media['extended']['type']] .'" />';
          $slides[]= l($thumbnail, $media['content'], $options);
        }
        else {
          $options['attributes']['class'][] = 'no-thumbnail';
          $slides[] .= l(t($type . ' #'. $media_cnt[$media['extended']['type']]) .'<span></span>', $media['content'], $options);
        }
//        if ($media['extended']['type'] === 'video' || $media['extended']['type'] === 'audio') {
//          $id = 'video-'. $delta .'-'. $key;
//          $item = array(
//            'file' => $media['content'],
//            'image' => isset($media['extended']['thumbnail']) ? $media['extended']['thumbnail'] : $theme .'/images/media-placeholder.png'
//          );
//          $output_slide .= '<div class="mediaplayer-wrapper">' . theme('si_jw_player', array('source' => $item, 'html_id' => $id, 'preset' => 'default')) .'</div>';
//        }
        if ($media['extended']['type'] === 'video') {
          if (isset($media['rendered'])) {
            $output_slide .='<div class="mediaplayer-wrapper"><div class="wrapper--video">'. $media['rendered'] .'</div></div>';
          }
          else {
            $id = 'video-'. $delta .'-'. $key;
            $item = array(
              'file' => $media['content'],
              'image' => isset($media['extended']['thumbnail'])  ? $media['extended']['thumbnail'] : $theme .'/images/media-placeholder.png'
            );
            $output_slide .= '<div class="mediaplayer-wrapper">' . theme('si_jw_player', array('source' => $item, 'html_id' => $id, 'preset' => 'default')) .'</div>';

          }
        }
        if($media['extended']['type'] === 'audio') {
          $id = 'audio-'. $delta .'-'. $key;
          $item = array(
            'file' => $media['content'],
            'image' => $theme .'/images/media-placeholder.png'
          );
          $output_slide .= '<div class="mediaplayer-wrapper">' . theme('si_jw_player', array('source' => $item, 'html_id' => $id, 'preset' => 'audio')) .'</div>';
        }

        //settings to pass to javascript to build media container.
        $settings['images'][$id] = array(
          'src' => array(
            'default' => $media['content'],
            'mobile' => isset($media['extended']['medium_size']) ? $media['extended']['medium_size'] : $media['content'],
            'fullscreen' => !empty($media['extended']['idsData']) ? $media['extended']['idsData']['idsURL'] .'?id='. $media['extended']['idsData']['idsID'] : $media['content']
          ),
          'type' => $media['extended']['type'],
          'info' => $media['extended']['alt_text'] . ' #'. $media_cnt[$media['extended']['type']],
          'caption' => $caption,
        );
        $media_cnt[$media['extended']['type']]++;
      }
      $output_slide .= '<div class="swiper-container-wrapper';
      $output_slide .= $cnt > 4 ? ' has-nav">' : '"">';
      $output_slide .= '<div id="'. $slideID .'" class="thumbnail-container';
      if($cnt > 4) {
        $output_slide .= ' swiper-container">';
        $output_slide .='<ul class="float-list reset-list thumbnail-wrapper swiper-wrapper">';
        $class = 'swiper-slide item';
      }
      else {
        $output_slide .='"><ul class="float-list reset-list thumbnail-wrapper">';
        $class = 'item';
      }

      foreach($slides as $slide) {
        $output_slide .= '<li class="' .$class .'">'. $slide .'</li>';
      }
      $output_slide .= '</ul>';
      $output_slide .= $cnt > 4 ? '<div class="swiper-pagination"></div><div class="swiper-button-prev"></div><div class="swiper-button-next"></div></div>': '</div>';
      $output_slide .= '</div>';

      if ($cnt > 3) {
        drupal_add_js(drupal_get_path('theme', 'si_baseline') .'/js/swiper.jquery.min.js', array('scope' => 'footer'));
        $settings['slideshow'][$slideID] = $slideID;
      }
    }
  }

  if (isset($assets['other'])) {
    $output_other = '<div class="links">';
    foreach ($assets['other'] as $key => $media) {
        $num = $key + 1;
        $title = isset($media['extended']['record_title']) ? $media['extended']['record_title'] : '';
      $text = t('View Online Resource <span class="sr-only"> @num for @title</span>',array('@num' => $num, '@title' => $title));
        $output_other .= l($text, $media['content'], array('attributes' => array('class' => array('btn', 'btn-large'), 'target' => '_blank'), 'html' => TRUE));
    }
    $output_other .= '</ul>';
  }
  drupal_add_js(drupal_get_path('theme', 'si_baseline') .'/js/media.js', array('scope' => 'footer'));

  if (!empty($settings)) {
    drupal_add_js(array('siMedia' => $settings), 'setting');

  }
  //dpm($settings);
  $end = microtime(TRUE);
  if (defined('EDAN_TEST') && EDAN_TEST) {$GLOBALS['EDAN_TEST']['si_edan_media'][] = $end-$start; }

  return $output_slide . $output_other;
}


function getIDS($url) {
  $idsData = array();
  $ids_url = 'https://ids.si.edu/ids/deliveryService';
  $ids_dynamic = 'https://ids.si.edu/ids/dynamic';
  $constrains = array(
    'max',
    'max_h',
    'max_w'
  );

  $link = drupal_parse_url($url);
  $query = isset($link['query']) ? $link['query'] : array();
  foreach($query as $key => $value) {
    if(in_array($key, $constrains)) {
      unset($query[$key]);
    }
  }
  $parsed = isset($link['path']) ? parse_url($link['path']) : array();

  //in case there's no idsId but the url has the ids link in it
  if(isset($query['id']) && !isset($media['idsId']) && strstr($parsed['host'], 'ids.si.edu')) {
    $media['idsId'] =  $query['id'];
  }
  $idsID = isset($media['idsId']) ? $media['idsId'] : (strstr($link['path'], 'si.edu') ? $link['path'] : '');
  if (!empty($idsID)) {
    $idsID = str_replace('/192X192', '', $idsID);
    // unset the id and constrain keys if it's part of the query array
    if (!empty($query)) {
      if(isset($query['id'])) {
        unset($query['id']);
      }
    }
    $idsData = array(
      'idsURL' => $ids_url,
      'idsID' => $idsID,
      'options' => array(
        'query' => $query,
        'fragment' => $link['fragment']
      ),
      'idsDynamic' => $ids_dynamic .'?id=' . $idsID .'&container.fullpage',
    );
  }

  return $idsData;

}
