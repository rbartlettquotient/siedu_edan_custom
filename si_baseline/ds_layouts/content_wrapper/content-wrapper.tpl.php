<?php

  /**
   * @file
   * Display Suite fluid 2 column stacked template.
   */
//  dpm($variables);
?>
<<?php print $layout_wrapper;
  print $layout_attributes; ?> class="content-wrapper <?php print $classes; ?> cf">

<?php if (isset($title_suffix['contextual_links'])): ?>
  <?php print render($title_suffix['contextual_links']); ?>
<?php endif; ?>
<?php if ($header): ?>
  <<?php print $header_wrapper ?> class="group-header<?php print $header_classes; ?>">
    <div class="header-theme"></div>

      <?php print $header; ?>


  </<?php print $header_wrapper ?>>
<?php endif; ?>
<?php if ($main_content): ?>
  <div class="content">
    <<?php print $main_content_wrapper ?><?php print $main_content_classes ? ' class="'. $main_content_classes .'"' : ''; ?>>
    <?php print $main_content; ?>
    </<?php print $main_content_wrapper ?>>
  </div>

<?php endif; ?>

</<?php print $layout_wrapper ?>>

<?php if (!empty($drupal_render_children)): ?>
  <?php print $drupal_render_children ?>
<?php endif; ?>
