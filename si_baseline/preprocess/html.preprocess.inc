<?php

/**
 * @file
 * Contains a pre-process hook for 'html'.
 */

/**
 * Implements hook_preprocess_html().
 */
function si_baseline_preprocess_html(&$vars, $hook) {

  global $base_url;
  // You can use preprocess hooks to modify the variables before they are passed
  // to the theme function or template file.
  if (user_is_anonymous()){
    drupal_add_js(drupal_get_path('theme', 'si_baseline') .'/js/colorbox-gs.js', array('scope' => 'footer', 'weight' => 10));
  }

  if(arg(0) == 'node' && is_numeric(arg(1))) {
    $node = node_load(arg(1));
    if ($node->type == 'dashboard' && isset($node->field_theme[LANGUAGE_NONE])) {
      $vars['classes_array'][] =  'node--dashboard';
      $vars['classes_array'][] = $node->field_theme[LANGUAGE_NONE][0]['value'];

    }
  }
  // Return early, so the maintenance page does not call any of the code below.
  if ($hook != 'html') {
    return;
  }
  $path = drupal_get_path('theme', 'si_baseline');
  $theme_path = url($path,  array('absolute' => TRUE));

//  drupal_add_css($theme_path .'/css/si_baseline.ie-lte-8.css',
//    array(
//      'group' => CSS_THEME,
//      'browsers' => array('IE' => 'lte IE 8', '!IE' => FALSE),
//      'preprocess' => FALSE)
//  );
  $vars['theme_path'] = $theme_path;


  $params = drupal_get_query_parameters();
  if (isset($params['iframe']) || arg(0) == 'tableau') {
    $vars['theme_hook_suggestions'][] = 'html__colorbox';
    $vars['attributes_array']['class'][] = 'page--colorbox';
    $vars['classes_array'][] = 'page--colorbox';
  //  $vars['attributes_array']['class'] = array('page--colorbox');
  }

  $icons = cache_get('si_meta');
  if (empty($icons)) {
    $icons = array();
    $favicon_path = $theme_path .'/favicon/';
    $icons['favicon'] = array(
      '#tag' => 'link',
      '#attributes' => array(
        'rel' => 'shortcut icon',
        'type' => 'image/vnd.microsoft.icon',
        'href' => $favicon_path . 'favicon.ico',
      ),
      '#weight' => 200
    );
    $icons['favicon2'] = array(
      '#tag' => 'link',
      '#attributes' => array(
        'rel' => 'shortcut icon',
        'type' => 'image/ico',
        'href' => $favicon_path . 'favicon.ico',
      ),
      '#weight' => 200
    );

    $favicons = array(
      'manifest' => array(
        '#tag' => 'link',
        '#attributes' => array(
          'rel' => 'manifest',
          'href' => $favicon_path . 'manifest.json',
        ),
      ),
      'safari' => array(
        '#tag' => 'link',
        '#attributes' => array(
          'rel' => 'mask-icon',
          'href' => $favicon_path . 'safari-pinned-tab.svg',
          'color' => '#0097d4'
        ),
      ),
      'theme_color' => array(
        '#tag' => 'meta',
        '#attributes' => array(
          'name' => 'theme-color',
          'content' => '#ffffff'
        ),
      ),
      'msColor' => array(
        '#tag' => 'meta',
        '#attributes' => array(
          'name' => 'msapplication-TileColor',
          'content' => '#ffffff'
        )
      ),
      'msImage' => array(
        '#tag' => 'meta',
        '#attributes' => array(
          'name' => 'msapplication-TileImage',
          'content' => $favicon_path . 'mstile-144x144.png',
        )
      ),
      'browserXML' => array(
        '#tag' => 'meta',
        '#attributes' => array(
          'name' => 'msapplication-config',
          'content' => $favicon_path . 'browserconfig.xml',
        ),
      ),
    );
    $i = 100;
//    $mask = '/^([a-z]+)?(-icon)?(-precomposed)?(-([0-9]+x[0-9]+))?\.png$/';
    $mask = '/^(\D+)?(-precomposed)?-([0-9]+x[0-9]+)?\.png$/';

    $path = $path . '/favicon';

    if ($files = file_scan_directory($path, $mask)) {
      foreach ($files as $file) {
        $matches = $icon = array();
        if (strstr($file->filename, 'mstile') == FALSE ) {
          preg_match($mask, $file->filename, $matches);
          // Run the filename through the regex once more picking up the
          // sub-matches in order to find out the dimensions of the touch icon
          $icon['href'] = file_create_url($file->uri);
          if (isset($matches[3])) {
            $icon['sizes'] = $matches[3];
          }
          if (strstr($file->filename, 'apple')) {
            $icon['rel'] = 'apple-touch-icon';
          }
          else {
            $icon['rel'] = 'icon';
            $icon['type'] = 'image/png';
          }
          $icons[$matches[0]] = array(
            '#tag' => 'link',
            '#attributes' => $icon,
            '#weight' => $i,
          );
          $i++;
        }
      }
    }
    foreach ($favicons as $delta => $data) {
      $data['#weight'] = $i;
      $icons[$delta] = $data;
      $i++;
    }
    cache_set('si_meta', $icons, 'cache');
  }
  else {
    $icons = $icons->data;
  }
  foreach($icons as $delta => $meta) {
    drupal_add_html_head($meta, 'si_baseine_'. $delta);
  }
}
