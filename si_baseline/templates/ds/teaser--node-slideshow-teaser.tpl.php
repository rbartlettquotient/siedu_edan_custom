<?php
/**
 * @file
 * article.tpl.php
 */
//dpm($variables);

  $element = $variables['elements'];
  $link_path = array();
  $ds = ds_get_layout($element['#entity_type'], $element['#bundle'], $element['#view_mode']);
  if (isset($ds['settings']['regions']['link_field'])) {
    foreach($ds['settings']['regions']['link_field'] as $field_name) {
      $field = field_info_field($field_name);
      if ($field['type'] == 'link_field' && isset($variables[$field_name]) && !empty($variables[$field_name])) {
        $path = current($variables[$field_name]);
       // dpm($path);
        $url = array_shift($path);
        $class = 'teaser-link inner';
        $class .= isset($path['attributes']['class']) ? ' '. $path['attributes']['class']: '';
        $path['attributes']['class'] = $class;
        $link_path = array(
          'url' => url($url, $path),
          'attributes' => $path['attributes']
        );
        $link_path['attributes']['class'] = 'inner';
      }
    }
  }
  if (empty($link_path) && $element['#entity_type'] == 'node' && $element['#view_mode'] == 'teaser_long') {
    $uri = entity_uri('node', $element['#node']);
    $link_path  = array(
      'url' => url($uri['path'], $uri['options']),
      'attributes' => array(
        'class' => 'inner'
      )
    );
  }

  $classes_media = 'b-media-wrapper';
if ($media_classes) {
  $classes_media .= ' '. trim($media_classes);
}
$classes_media = ' class="'. $classes_media .'"';

  $classes_content = 'b-text-wrapper caption';
if ($teaser_content_classes) {
  $classes_content .=' '. trim($teaser_content_classes);
}
  $classes_content = ' class="'. $classes_content .'"';

?>
<div class="<?php print $classes; ?><?php print $media && $media != "&nbsp;" ? ' has-media' : '' ?>"<?php print $attributes; ?>>
  <?php if(!empty($link_path)): ?>
    <a href="<?php print $link_path['url']; ?>"<?php print isset($link_path['attributes']) ? drupal_attributes($link_path['attributes']) :''?>>

    <?php else: ?>
    <div class="inner">
  <?php  endif; ?>
  <?php if ($media && $media != "&nbsp;"): ?>
    <div<?php print $classes_media; ?>><?php print ($media); ?></div>
  <?php endif; ?>

  <?php if ($teaser_content && $teaser_content != "&nbsp;"): ?>
    <div<?php print $classes_content; ?>>
      <?php print ($teaser_content); ?></div>
  <?php endif; ?>

  <?php if($link_path): ?>
    </a>
  <?php  else: ?>
      </div>
  <?php  endif; ?>
</div>
