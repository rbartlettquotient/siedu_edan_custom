
<?php
if(module_exists('devel') && isset($_GET['dpm']) && user_access('access devel information')){
  dpm($variables);
}

elseif (isset($_GET['dump'])) {
  var_export($variables);
}
?>


  <?php if ($facets): ?>
    <div class="filter-wrapper default">
      <?php echo $facets; ?>
    </div>
  <?php endif; ?>
  <div id="search-<?php print $id; ?>" class="l-container search-results-container grid-wrapper equal-col">
  <?php if (!empty($docs)): ?>
    <ul class="search-results <?php print $results_class; ?> content">
      <?php foreach ($docs as $doc): ?>

        <li class="col-sm-6 col-md-4 col spacing-bottom" id="<?php print $doc['row_attributes']['id']; ?>">
          <div class="node node--teaser node--teaser-long node--teaser--teaser-long">

              <a href="<?php print $doc['#record_link'] ? $doc['#record_link'] : '#'; ?>" class="inner">
                <?php if($doc['img_uri']): ?>
                  <div class="b-media-wrapper field--type-image">
                    <img src="<?php print $doc['img_uri']; ?>" />
                  </div>
                <?php endif; ?>

                <div class="b-text-wrapper">
                  <h3 class="title">
                    <?php print $doc['#title_plain'];?>
                  </h3>
                  <?php if(isset($doc['teaser']) || $doc['description']): ?>
                  <div class="description">
                    <?php print isset($doc['teaser']) ? $doc['teaser'] : $doc['description']; ?>
                  </div>
                    <?php endif; ?>

                </div>

              </a>

          </div>

        </li>

      <?php endforeach; ?>

    </ul>

    <?php if ($pager): ?>
      <div id="placeholder"></div>
      <?php print $pager; ?>
    <?php endif; ?>
     <?php else: ?>
    <p><?php print $empty_msg; ?></p>
  <?php endif; ?>
  </div>

