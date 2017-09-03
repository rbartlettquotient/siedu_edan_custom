<?php


/**
 * Imprementation hook_preprocess_edan_location_page
 */

function si_baseline_preprocess_edan_location_page(&$vars) {
  drupal_set_title(t('@location', array('@location' => $vars['title'])));
  $content = $vars['content'];
  $vars['tabs'] = $vars['accordion'] =  $vars['img_uri'] = '';
  $tabs = $titles = array();
  $i = $j = 0;
  //build regular tabs
  if (isset($vars['objectGroup']['search_results']) && !empty($vars['objectGroup']['search_results'])) {
    $tabs[$i] = $vars['objectGroup']['search_results'];
    $tabs[$i] .= '<p class="align-right">'. t('Collection items shown may not be on view.') . '</p>';
    $titles[$i] = t('Collections Sampler');
    $i++;
  }
  if (!empty($vars['exhibition_content'])) {
//    $exhibit_link = url('exhibitions', array(
//      'query' =>
//        array(
//          'edan_fq' => array('p.event.location.extended.location_id:' .$vars['edan_id'])
//    )));
    $exhibit_link = url('exhibitions');
    $tabs[$i] = $vars['exhibition_content'];
    $tabs[$i] .= '<p class="align-right"><a href="'. $exhibit_link .'">'. t('View all exhibitions') .'</a></p>';
    $titles[$i] = t('Exhibitions');
    $i++;
  }

  if(!empty($content['trumba_venue_ID'])) {
    $tabs[$i] = '<div id="divSpud-'. $content['trumba_venue_ID'] .'"></div>';
    $tabs[$i] .= '<p class="align-right"><a href="'. url('node/21') .'">'. t('View all events') .'</a></p>';
    $titles[$i] = t('Events');
    $settings['trumbaID'] = $content['trumba_venue_ID'];
    drupal_add_js('https://www.trumba.com/scripts/spuds.js', 'external', array('scope' => 'footer', 'weight' => 0));
    drupal_add_js(array('siTrumba' => $settings), 'setting');
    $i++;
  }


  if (!empty($tabs)) {
    $vars['tabs'] = array(
      'tabs' => $tabs,
      'titles' => $titles,
      'tabID' => 'tabs-' . $content['id'],
      'tabMode' => 'responsive_tab',
      'mobileCollapsed' => 1
    );
    drupal_add_js(drupal_get_path('theme', 'si_baseline') .'/js/location.js', array('scope' => 'footer', 'weight' => 10));
  }

  $vars['floorplan'] = isset($content['grouped_media']['pdf'][0]['content']) && strstr($content['grouped_media']['pdf'][0]['extended']['description'], 'floor') ? l('<span class="text">' . t('Floor Plan') . '</span>', $content['grouped_media']['pdf'][0]['content'], array('attributes' => array('class' => array('icon--floor-plan'), 'target' => '_blank'), 'html' => TRUE)) : '';

  if (!empty($content['images'])) {
    $image = current($content['images']);
    $vars['img_uri'] = $image['content'];
  }


  //accordion tabs
  $tabs = $titles = array();
  $view =  views_get_view_result('dining', 'block_1', $vars['content']['id']);
  if (!empty($view)) {
    $tabs[$j] = views_embed_view('dining', 'block_1', $vars['content']['id']);
    $titles[$j] = t('Dining');
    $j++;
  }

  if (isset($content['accessibility_services']) && !empty($content['accessibility_services'])) {
    $tabs[$j] = $content['accessibility_services'];
    $titles[$j] = t('Accessibility Services');
  }
  $logistics = '';
  if (isset($content['parking']) && !empty($content['parking'])) {
    //$logistics .= '<h4>'. t('Parking') .'</h4>';
    $logistics .=  $content['parking'] ;
  }
  if (isset($content['public_transportation']['extended']['metro']) && !empty($content['public_transportation']['extended']['metro'])) {
    //$logistics .= '<h4>'. t('Metro') .'</p>';
    $logistics .= $content['public_transportation']['extended']['metro'] ;
  }
  if (isset($content['public_transportation']['extended']['bus']) && !empty($content['public_transportation']['extended']['bus'])) {
    //$logistics .= '<h4>'. t('Bus') .'</h4>';
    $logistics .= $content['public_transportation']['extended']['bus']  ;
  }
  if($logistics !== '') {
  $tabs[$j] = $logistics;
  $titles[$j] = t('Getting Here');
  }

  $vars['accordion'] = array(
    'tabs' => $tabs,
    'titles' => $titles,
    'tabID' => 'accordion-' . $content['id'],
    'tabMode' => 'accordion_tab',
  );
  $vars['full_address'] = si_baseline_get_address($vars);
  if (isset($vars['content']['record_link'])) {
    $parsed = parse_url($vars['content']['record_link']);
    $vars['location_link'] = l($parsed['host'], $vars['content']['record_link']);

  }
//  dpm($parsed);
  //dpm($vars);

}

function si_baseline_get_address($unit) {
  $address = '';
  $address1 = isset($unit['content']['address']['extended']['street_address']) && strlen(trim($unit['content']['address']['extended']['street_address'])) > 0 ?
    $unit['content']['address']['extended']['street_address'] : '';
  $address1 .= isset($unit['content']['address']['extended']['street_address2']) && strlen(trim($unit['content']['address']['extended']['street_address2'])) > 0 ?
    '<br />'/ $unit['content']['address']['extended']['street_address2'] : '';
  $address2 = strlen(trim($unit['content']['address']['extended']['city'])) > 0 ?
    $unit['content']['address']['extended']['city'] . ', ' : '';
  $address2 .= strlen(trim($unit['content']['address']['extended']['state'])) > 0 ?
    $unit['content']['address']['extended']['state'] .' ' : '';
  $address2 .= isset($unit['content']['address']['extended']['postalcode']) &&
               strlen(trim($unit['content']['address']['extended']['postalcode'])) > 0 ?
               $unit['content']['address']['extended']['postalcode'] : '';
  $address = strlen($address1) > 0 ? $address1 . '<br />'  : '';
  $address .= strlen($address2) > 0 ? $address2  : '';

  return $address;
}
