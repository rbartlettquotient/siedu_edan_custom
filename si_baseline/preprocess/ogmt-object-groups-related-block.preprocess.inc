<?php

/**
 * Implements hook_preprocess_ogmt_object_groups_related_block().
 */
function si_baseline_preprocess_ogmt_object_groups_related_block(&$vars) {

  foreach ($vars['rows'] as $i => $row) {
    $feature = '';

    $vars['rows'][$i]['description'] = _ogmt_render_content($row['description']);
    $vars['rows'][$i]['list_title'] = isset($row['content']['listTitle']) && strlen($row['content']['listTitle']) > 0 ? $row['content']['listTitle'] : $row['#title_plain'];

    $image_settings = variable_get('siedu_edan_image');
    $thumbnail = isset($image_settings['thumbnail']) ? $image_settings['thumbnail']['size'] : 200;

    if (!empty($row['images']) && is_array($row['images'])) {
      $image = current($row['images']);
      $theme_vars = array(
        'path' => $image['extended']['thumbnail'],
        'alt' => '',
        'title' => '',
        'attributes' => array('class' => 'ogmt-object-group-img'),
      );
      if (!empty($image['extended']['idsData'])) {
        $theme_vars['width'] = $thumbnail;
      }
      $feature = theme('image', $theme_vars);
    }

    $vars['rows'][$i]['feature'] = $feature;
    $vars['rows'][$i]['feature_raw'] = isset($image) ? $image : array();

    $rendered_image = '';
    $result_class = 'node--teaser node--teaser-long';

    if (!empty($vars['rows'][$i]['feature_raw'])) {
      $result_class .= ' has-media';
      if (module_exists('picture') && !empty($vars['rows'][$i]['feature_raw']['extended']['idsData'])) {
        $img_scr = $vars['rows'][$i]['feature_raw']['extended']['idsData']['idsURL'] . '?id=' . $vars['rows'][$i]['feature_raw']['extended']['idsData']['idsID'] . '&max_w=';

        $image_info = array(
          'uri' => $img_scr . '300',
          'path' => NULL,
          'width' => NULL,
          'height' => NULL,
          'alt' => '',
          'title' => NULL,
          'attributes' => array(),
          'srcset' => array(
            array(
              'uri' => $img_scr . '230',
              'width' => '230w'
            ),
            array(
              'uri' => $img_scr . '400',
              'width' => '400w'
            ),
          ),
          'sizes' => '(min-width: 500px) 50%, (min-width: 980px)  33%, (min-width: 1280px) 25%, 100%',
        );
        $rendered_image = theme('image_srcset', $image_info);
      }
      elseif (!empty($vars['rows'][$i]['feature_raw']['content'])) {
        $image_info = array(
          'src' => $vars['rows'][$i]['feature_raw']['content'],
          'alt' => ''
        );

        $rendered_image = '<img' . drupal_attributes($image_info) . ' />';
      }
    }

    $vars['rows'][$i]['rendered_image'] = $rendered_image;
    $vars['rows'][$i]['result_class'] = $result_class;

  }

}