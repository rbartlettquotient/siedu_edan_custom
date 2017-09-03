<?php

if(module_exists('devel') && isset($_GET['dpm']) && user_access('access devel information')){
  dpm($variables);
}

elseif (isset($_GET['dump'])) {
  var_export($variables['docs']);
}
?>
  <?php if ($facets): ?>
    <div class="filter-wrapper default">
      <?php echo $facets; ?>
    </div>
  <?php endif; ?>
  <div class="search-results-wrapper">
<div id="search-<?php print $id; ?>" class="<?php print $container_class?>">
  <?php if (!empty($docs)): ?>
  <ul class="<?php print $results_class; ?>">

    <?php foreach ($docs as $doc): ?>
      <li <?php print drupal_attributes($doc['row_attributes']); ?>>
        <?php if($doc['result_class']): ?>
        <div class="<?php print $doc['result_class']; ?>">
          <?php endif; ?>
          <?php if($search_name == 'video'): ?>
            <a href="<?php echo $doc['#title_link']['rendered_path'] ?>" class="inner colorbox-load">
              <?php if (isset($doc['rendered_image']) && !empty($doc['rendered_image'])): ?>
                <div class="b-media-wrapper field--type-image">
                  <?php print $doc['rendered_image']; ?>
                </div>
              <?php endif; ?>
              <div class="b-text-wrapper">
                <h3 class="title delta"><?php echo $doc['#title_plain']; ?></h3>
              </div>
            </a>
          <?php else: ?>
            <div class="inner">
              <?php if (isset($doc['rendered_image']) && !empty($doc['rendered_image'])): ?>
                <div class="b-media-wrapper field--type-image">
                  <?php if (isset($doc['#title_link']['rendered_path'])): ?>
                    <a href="<?php echo $doc['#title_link']['rendered_path'] ?>" class="colorbox-load">
                  <?php endif; ?>
                  <?php echo $doc['rendered_image']; ?>
                    <?php if (isset($doc['#title_link']['rendered_path'])): ?>
                      </a>
                <?php endif; ?>

                </div>
              <?php endif; ?>
              <div class="b-text-wrapper">
                <?php if(isset($doc['preface'])): ?>
                  <div class="preface">
                    <?php print $doc['preface']; ?>
                  </div>
                <?php endif; ?>
                <h3 class="title delta"><?php print $doc['#title']; ?></h3>
                <?php if($doc['description']): ?>
                  <div class="description">
                    <?php print $doc['description']; ?>
                  </div>
                <?php endif; ?>
              </div>
            </div>
          <?php endif; ?>
          <?php if($doc['result_class']): ?>
        </div>
      <?php endif; ?>
      </li>
    <?php endforeach; ?>
  </ul>
  <div id="placeholder"></div>
  <?php echo $pager; ?>
  <?php else: ?>
    <p><?php print $empty_msg; ?></p>
  <?php endif; ?>

</div>
