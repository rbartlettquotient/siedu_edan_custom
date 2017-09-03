<?php

  /**
   * @file
   * Display Suite fluid 2 column stacked template.
   */

  // Add sidebar classes so that we can apply the correct width in css.
  if (($left && !$right) || ($right && !$left)) {
    $classes .= ' group-one-column';
  }
  else {
    $classes .= ' layout nested';
  }
//  if ($left && $right) {
//    $left_classes .= 'col col-sm-6';
//    $right_classes .= 'col col-sm-6 last';
//  }
?>
<<?php print $layout_wrapper;
  print $layout_attributes; ?> class="ds-2col-stacked-fluid <?php print $classes; ?> clearfix">

<?php if (isset($title_suffix['contextual_links'])): ?>
  <?php print render($title_suffix['contextual_links']); ?>
<?php endif; ?>
<?php if ($header): ?>
  <<?php print $header_wrapper ?> class="group-header<?php print $header_classes; ?>">
    <div class="header-theme"></div>
    <?php print $header; ?>
  </<?php print $header_wrapper ?>>
<?php endif; ?>
<?php if ($left || $right): ?>
  <div class="content">
  <?php if ($left): ?>
    <<?php print $left_wrapper ?> class="group-left<?php print $left_classes; ?>">
    <?php print $left; ?>
    </<?php print $left_wrapper ?>>
  <?php endif; ?>

  <?php if ($right): ?>
    <<?php print $right_wrapper ?> class="group-right<?php print $right_classes; ?>">
    <?php print $right; ?>
    </<?php print $right_wrapper ?>>
  <?php endif; ?>
  </div>

<?php endif; ?>
<?php if ($footer): ?>
  <<?php print $footer_wrapper ?> class="group-footer<?php print $footer_classes; ?>">
  <?php print $footer; ?>
  </<?php print $footer_wrapper ?>>
<?php endif; ?>

</<?php print $layout_wrapper ?>>

<?php if (!empty($drupal_render_children)): ?>
  <?php print $drupal_render_children ?>
<?php endif; ?>
